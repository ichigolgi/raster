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

  // TODO: ������ӂ̏�����Texture�̕��Ɏ����Ă���
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
  //�J���[�e�[�u����ݒ肷��
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

  // ���f���o�^���Ȃ���
  m_scene.Clear();

  // ��ʍX�V���N�G�X�g
  UpdateWindowRequest(update_context);

  // Bit�X�V
  // BITMAP bitmap;
  // GetObject(m_hbitmap, sizeof(BITMAP), &bitmap);
  // GetObject(hbitmap, sizeof(BITMAP), &bitmap);
  // TODO: ������ӂ̏�����Texture�̕��Ɏ����Ă���
#if 1
  for (int yi = 0; yi < SCREEN_SIZE_H; ++yi) {
    for (int xi = 0; xi < SCREEN_SIZE_W; ++xi) {
      auto pixel = m_backbuffer_texture.GetPixel(xi, yi);
      // int dib_i = (xi + yi * SCREEN_SIZE_W); // �����ł����́H�H�H
      int dib_i = (xi + (SCREEN_SIZE_H - yi - 1) *
                            SCREEN_SIZE_W); // ������Ȃ̂�y���t
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
        255.f * ((float)i / SCREEN_PIXELS)); //���ʂ͂Ȃ���BGR�ɂȂ��Ă�
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
          );                                       //���ʂ͂Ȃ���BGR�ɂȂ��Ă�
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
    pool = RGB(0, 0, 255); //���ʂ͂Ȃ���BGR�ɂȂ��Ă�
  }
#endif
}

void CEngine::Draw(DrawContext &draw_context) {
  if (!m_is_initialized) {
    return;
  }

  // Scene�ɓo�^���ꂽ���f�����o�b�N�o�b�t�@�ɕ`�悷��
  DrawModel(draw_context);

  // �o�b�N�o�b�t�@�e�N�X�`���`��
  DrawBackbuffer(draw_context);
}

//
// CEngine private method
//

void CEngine::UpdateWindowRequest(UpdateContext &update_context) {
  // Draw���Ăяo��
  // - ���L2�̊֐����ĂԂ�WM_PAINT���Ă΂��
  InvalidateRect(m_hwnd, NULL, TRUE); //�̈斳����
  UpdateWindow(m_hwnd);               //�ĕ`�施��
}

void CEngine::DrawModel(DrawContext &draw_context) {
  for (auto *mesh : m_scene.polygons) {
    CVertexShader vs;
    CRasterizer raster;
    CPixelShader ps;

#if 0 // underconstruction
    // TODO: �|���S�����Ƃɏ���
    for () {
      // ���_�V�F�[�_�𑖂点��

      // ���X�^���C�U�Ŏ��ۂɕ`�悷��s�N�Z�������肷��

      // �Ώۂ̃s�N�Z���ɑ΂��ăs�N�Z���V�F�[�_�ŐF��t����
    }
#endif
  }
}

void CEngine::DrawBackbuffer(DrawContext &draw_context) {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(m_hwnd, &ps);

  HDC hdcMem = CreateCompatibleDC(hdc);
  HGDIOBJ hOldObj = SelectObject(hdcMem, m_hbitmap);

  // DIB�ō����Bit�̕`��
  int ret = StretchDIBits(hdc, 0, 0, SCREEN_SIZE_W, SCREEN_SIZE_H, 0, 0,
                          SCREEN_SIZE_W, SCREEN_SIZE_H, (VOID *)S_BIT_POOL,
                          m_pbitmapinfo, DIB_RGB_COLORS, SRCCOPY);
  assert(ret != GDI_ERROR);

  SelectObject(hdcMem, hOldObj); // ���A
  DeleteDC(hdcMem);
  EndPaint(m_hwnd, &ps);
}
