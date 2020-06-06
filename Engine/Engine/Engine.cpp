#include "stdafx.h"
#include "Engine.h"
#include <cassert>

namespace 
{
	enum { 
		BIT_NUM = 32, 
		BYTE_NUM = BIT_NUM/8,
	};
	DWORD S_BIT_POOL[SCREEN_PIXELS * BYTE_NUM]{};
}

//
// CEngine public method
//


void CEngine::Initialize(InitializeContext& initialize_context)
{
	m_hwnd = initialize_context.hwnd;

	int planes = 1;
	int bits_per_pel = 8;
#if 1
	int color_num = pow(2, (int)BIT_NUM);
	m_pbitmapinfo = (LPBITMAPINFO)HeapAlloc(
		GetProcessHeap(),
		HEAP_ZERO_MEMORY, 
		sizeof(BITMAPINFO) + sizeof(RGBQUAD)*(color_num - 1)
	);

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

	auto hdc = GetDC(m_hwnd);;
	m_hbitmap = CreateDIBSection(
		hdc,
		m_pbitmapinfo,
		DIB_RGB_COLORS,
		(VOID**)&S_BIT_POOL,
		NULL,
		0
	);
#endif
	m_is_initialized = true;
}

void CEngine::Finalize()
{
	HeapFree(GetProcessHeap(), 0, m_pbitmapinfo);
	DeleteObject(m_hbitmap);//
	m_is_initialized = false;
}

void CEngine::Update(UpdateContext& update_context)
{
	if (!m_is_initialized)
	{
		return;
	}

	// 画面更新リクエスト
	UpdateWindowRequest(update_context);

	// Bit更新
	//BITMAP bitmap;
	//GetObject(m_hbitmap, sizeof(BITMAP), &bitmap);
	//GetObject(hbitmap, sizeof(BITMAP), &bitmap);
	for (int yi = 0; yi < SCREEN_SIZE_H; ++yi)
	{
		for (int xi = 0; xi < SCREEN_SIZE_W; ++xi)
		{
			auto pixel = m_backbuffer_texture.GetPixel(xi, yi);
			//int dib_i = (xi + (SCREEN_SIZE_W - yi) * SCREEN_SIZE_W);
			int dib_i = (xi + yi * SCREEN_SIZE_W);
			S_BIT_POOL[dib_i] = RGB(pixel.b * 255.f, pixel.g * 255.f, pixel.r * 255.f);
		}
	}
#if 0
	for (auto& pool : S_BIT_POOL)
	{
		pool = RGB(0, 0, 255);//結果はなぜかBGRになってる
	}
#endif
}

void CEngine::Draw(DrawContext& draw_context) 
{
	if (!m_is_initialized)
	{
		return;
	}

	// バックバッファテクスチャ描画
	DrawBackbuffer(draw_context);
}

//
// CEngine private method
//

void CEngine::UpdateWindowRequest(UpdateContext& update_context)
{
	// Drawを呼び出す
	// - 下記2つの関数を呼ぶとWM_PAINTが呼ばれる
	InvalidateRect(m_hwnd, NULL, TRUE);//領域無効化
	UpdateWindow(m_hwnd);//再描画命令
}

void CEngine::DrawBackbuffer(DrawContext& draw_context)
{
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(m_hwnd, &ps);

	// テクスチャ描画
#if 0
// SetPixel だとくそおそいのでだめ
	for (int xi = 0; xi < SCREEN_SIZE_W; ++xi)
	{
		for (int yi = 0; yi < SCREEN_SIZE_H; ++yi)
		{
			auto pixel = m_backbuffer_texture.GetPixel(xi, yi);
			COLORREF color;
			color = RGB((int)pixel.r * 255, (int)pixel.g * 255, (int)pixel.b * 255);
			int x = xi;
			int y = yi;
			SetPixel(hdc, x, y, color);
		}
	}
#else
	HDC hdcMem = CreateCompatibleDC(hdc);
	HGDIOBJ hOldObj = SelectObject(hdcMem, m_hbitmap);
	
	// Bit描画
#if 0
	int rop = 0;
	BitBlt(
		hdc,
		0,
		0,
		SCREEN_SIZE_W,
		SCREEN_SIZE_H,
		hdcMem,
		0,
		0,
		SRCCOPY
	);
#else
	int ret = StretchDIBits(
		hdc,
		0,
		0,
		SCREEN_SIZE_W,
		SCREEN_SIZE_H,
		0,
		0,
		SCREEN_SIZE_W,
		SCREEN_SIZE_H,
		(VOID*)S_BIT_POOL,
		m_pbitmapinfo,
		DIB_RGB_COLORS,
		SRCCOPY
	);
	assert(ret != GDI_ERROR);
#endif
	SelectObject(hdcMem, hOldObj); // 復帰
	DeleteDC(hdcMem);
#endif

	EndPaint(m_hwnd, &ps);
}
