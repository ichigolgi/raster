#include "stdafx.h"
#include "Engine.h"
#include <cassert>
//
#include "PixelShader.h"
#include "Rasterizer.h"
#include "Scene.h"
#include "VertexShader.h"
//

namespace {
enum {
  BIT_NUM = 32,
  BYTE_NUM = BIT_NUM / 8,
};
//	DWORD S_BIT_POOL[SCREEN_PIXELS * BYTE_NUM]{};
DWORD S_BIT_POOL[SCREEN_PIXELS]{};
} // namespace

//
// CEngine public method
//

void CEngine::Initialize(InitializeContext &initialize_context) {
  m_hwnd = initialize_context.hwnd;

  // TODO: ここら辺の処理をTextureの方に持っていく
  int planes = 1;
  int bits_per_pel = 8;
#if 1
  int color_num = pow(2, (int)BIT_NUM);
  m_pbitmapinfo = (LPBITMAPINFO)HeapAlloc(
      GetProcessHeap(), HEAP_ZERO_MEMORY,
      sizeof(BITMAPINFO) + sizeof(RGBQUAD) * (color_num - 1));

  m_pbitmapinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  m_pbitmapinfo->bmiHeader.biWidth = SCREEN_SIZE_W;
  m_pbitmapinfo->bmiHeader.biHeight = SCREEN_SIZE_H;
  m_pbitmapinfo->bmiHeader.biPlanes = 1;
  m_pbitmapinfo->bmiHeader.biBitCount = BIT_NUM;
  m_pbitmapinfo->bmiHeader.biCompression = BI_RGB;
  //カラーテーブルを設定する
#if 0
	for (int i = 0; i<color_num; i++) {
		m_pbitmapinfo->bmiColors[i].rgbBlue = i % 128;
		m_pbitmapinfo->bmiColors[i].rgbGreen = 128 - i % 128;
		m_pbitmapinfo->bmiColors[i].rgbRed = i % 256;
	}
#endif

  auto hdc = GetDC(m_hwnd);
  ;
  m_hbitmap = CreateDIBSection(hdc, m_pbitmapinfo, DIB_RGB_COLORS,
                               (VOID **)&S_BIT_POOL, NULL, 0);
#endif
  m_is_initialized = true;
}

void CEngine::Finalize() {
  HeapFree(GetProcessHeap(), 0, m_pbitmapinfo);
  DeleteObject(m_hbitmap); //
  m_is_initialized = false;
}

void CEngine::Update(UpdateContext &update_context) {
  if (!m_is_initialized) {
    return;
  }

  // モデル登録しなおし
  m_scene.Clear();

  // 画面更新リクエスト
  UpdateWindowRequest(update_context);

  // Bit更新
  // BITMAP bitmap;
  // GetObject(m_hbitmap, sizeof(BITMAP), &bitmap);
  // GetObject(hbitmap, sizeof(BITMAP), &bitmap);
  // TODO: ここら辺の処理をTextureの方に持っていく
#if 1
  for (int yi = 0; yi < SCREEN_SIZE_H; ++yi) {
    for (int xi = 0; xi < SCREEN_SIZE_W; ++xi) {
      auto pixel = m_backbuffer_texture.GetPixel(xi, yi);
      // int dib_i = (xi + yi * SCREEN_SIZE_W); // 左上基準でいいの？？？
      int dib_i = (xi + (SCREEN_SIZE_H - yi - 1) *
                            SCREEN_SIZE_W); // 左下基準なのでyが逆
      BYTE *color_byte = (BYTE *)(&S_BIT_POOL[dib_i]);
      color_byte[0] = (BYTE)(pixel.b * 255.f); // B
      color_byte[1] = (BYTE)(pixel.g * 255.f); // G
      color_byte[2] = (BYTE)(pixel.r * 255.f); // R
      color_byte[3] = 0;                       // -
    }
  }
#elif 0
  for (int i = 0; i < SCREEN_PIXELS; ++i) {
    S_BIT_POOL[i] = RGB(
        255.f * ((float)i / SCREEN_PIXELS), 255.f * ((float)i / SCREEN_PIXELS),
        255.f * ((float)i / SCREEN_PIXELS)); //結果はなぜかBGRになってる
  }
#elif 1
  for (int yi = 0; yi < SCREEN_SIZE_H; ++yi) {
    for (int xi = 0; xi < SCREEN_SIZE_W; ++xi) {
      auto pixel = m_backbuffer_texture.GetPixel(xi, yi);
      int dib_i = (xi + (SCREEN_SIZE_H - yi - 1) * SCREEN_SIZE_W);
      // int dib_i = (xi + yi * SCREEN_SIZE_W);
      S_BIT_POOL[dib_i] =
          RGB(0.f, // 255.f * ((float)dib_i / SCREEN_PIXELS) // B
              255.f * ((float)yi / SCREEN_SIZE_H), // G
              255.f * ((float)xi / SCREEN_SIZE_W), // R
          );                                       //結果はなぜかBGRになってる
    }
  }
#elif 1
  for (int yi = 0; yi < SCREEN_SIZE_H; ++yi) {
    for (int xi = 0; xi < SCREEN_SIZE_W; ++xi) {
      // auto pixel = m_backbuffer_texture.GetPixel(xi, yi);
      int dib_i = (xi + (SCREEN_SIZE_H - yi - 1) * SCREEN_SIZE_W);
      // int dib_i = (xi + yi * SCREEN_SIZE_W);
      BYTE *color_byte = (BYTE *)(&S_BIT_POOL[dib_i]);
      float value_index = (float)dib_i / (float)(SCREEN_PIXELS);
      float value_scaled = 255.f * value_index;
      BYTE value = (BYTE)(value_scaled);
      color_byte[0] = value; // B
      color_byte[1] = value; // G
      color_byte[2] = value; // R
      color_byte[3] = 0;     // -
    }
  }
#else
  for (auto &pool : S_BIT_POOL) {
    pool = RGB(0, 0, 255); //結果はなぜかBGRになってる
  }
#endif
}

void CEngine::Draw(DrawContext &draw_context) {
  if (!m_is_initialized) {
    return;
  }

  // Sceneに登録されたモデルをバックバッファに描画する
  DrawModel(draw_context);

  // バックバッファテクスチャ描画
  DrawBackbuffer(draw_context);
}

//
// CEngine private method
//

void CEngine::UpdateWindowRequest(UpdateContext &update_context) {
  // Drawを呼び出す
  // - 下記2つの関数を呼ぶとWM_PAINTが呼ばれる
  InvalidateRect(m_hwnd, NULL, TRUE); //領域無効化
  UpdateWindow(m_hwnd);               //再描画命令
}

void CEngine::DrawModel(DrawContext &draw_context) {
  for (auto *mesh : m_scene.polygons) {
    CVertexShader vs;
    CRasterizer raster;
    CPixelShader ps;

#if 0 // underconstruction
    // TODO: ポリゴンごとに処理
    for () {
      // 頂点シェーダを走らせる

      // ラスタライザで実際に描画するピクセルを決定する

      // 対象のピクセルに対してピクセルシェーダで色を付ける
    }
#endif
  }
}

void CEngine::DrawBackbuffer(DrawContext &draw_context) {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(m_hwnd, &ps);

  HDC hdcMem = CreateCompatibleDC(hdc);
  HGDIOBJ hOldObj = SelectObject(hdcMem, m_hbitmap);

  // DIBで作ったBitの描画
  int ret = StretchDIBits(hdc, 0, 0, SCREEN_SIZE_W, SCREEN_SIZE_H, 0, 0,
                          SCREEN_SIZE_W, SCREEN_SIZE_H, (VOID *)S_BIT_POOL,
                          m_pbitmapinfo, DIB_RGB_COLORS, SRCCOPY);
  assert(ret != GDI_ERROR);

  SelectObject(hdcMem, hOldObj); // 復帰
  DeleteDC(hdcMem);
  EndPaint(m_hwnd, &ps);
}
