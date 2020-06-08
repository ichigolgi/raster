#pragma once
#include "stdafx.h"
#include <array>

/* テクスチャ */
// 正確にはバックバッファ
struct Pixel
{
	float r;
	float g;
	float b;
	float depth;

	Pixel(const Pixel& src) : r(src.r), g(src.g), b(src.b), depth(src.depth){}
	Pixel() :r (0.f), g(1.f), b(0.f), depth(0.f) {}
};

class CTexture
{
public:
	CTexture() 
	{
		Clear();
	}
	~CTexture() {}

	Pixel& GetPixel(int index) { return m_elements.at(index); }
	Pixel& GetPixel(int x, int y)
	{
		int index = x + (y * SCREEN_SIZE_W);
		return m_elements.at(index);
	}
	void SetPixel(const Pixel& pixel, int index) { m_elements.at(index) = pixel; }
	void SetPixel(const Pixel& pixel, int x, int y)
	{
		int index = x + (y * SCREEN_SIZE_W);
		m_elements.at(index) = pixel;
	}

	void Clear()
	{
		for (int y = 0; y < SCREEN_SIZE_H; ++y)
		{
			for (int x = 0; x < SCREEN_SIZE_W; ++x)
			{
				int index = x + (y * SCREEN_SIZE_W);
				auto& p = m_elements.at(index);

				// 白クリア
				p.r = 1.f;
				p.g = 1.f;
				p.b = 1.f;
			}
		}
	}
	void ClearGray()
	{
		for (int y = 0; y < SCREEN_SIZE_H; ++y)
		{
			for (int x = 0; x < SCREEN_SIZE_W; ++x)
			{
				int index = x + (y * SCREEN_SIZE_W);
				auto& p = m_elements.at(index);

				// グレースケール
				float value = (float)index / (float)(SCREEN_PIXELS);
				p.r = value;
				p.g = value;
				p.b = value;
			}
		}
	}
	void ClearXAxis()
	{
		for (int y = 0; y < SCREEN_SIZE_H; ++y)
		{
			for (int x = 0; x < SCREEN_SIZE_W; ++x)
			{
				int index = x + (y * SCREEN_SIZE_W);
				auto& p = m_elements.at(index);
				p.r = (float)x / (float)(SCREEN_SIZE_W);
				p.g = 0.f;
				p.b = 0.f;
			}
		}
	}
	void ClearYAxis()
	{
		for (int y = 0; y < SCREEN_SIZE_H; ++y)
		{
			for (int x = 0; x < SCREEN_SIZE_W; ++x)
			{
				int index = x + (y * SCREEN_SIZE_W);
				auto& p = m_elements.at(index);
				p.r = 0.f;
				p.g = 0.f;
				p.b = (float)y / (float)(SCREEN_SIZE_H);;
			}
		}
	}
	void ClearAspect()
	{
		for (int y = 0; y < SCREEN_SIZE_H; ++y)
		{
			for (int x = 0; x < SCREEN_SIZE_W; ++x)
			{
				int index = x + (y * SCREEN_SIZE_W);
				auto& p = m_elements.at(index);
				p.r = 0.f;
				p.g = std::max<float>(0.f, 1.f - 1000.f * std::abs(((float)x / (float)y) - ((float)(SCREEN_SIZE_W) / (float)(SCREEN_SIZE_H))));
				p.b = 0.f;
			}
		}
	}

	// NOTE: 本来は SCREEN_SIZE_Wとかじゃなくてサイズ情報を自分で持つ

private:
	std::array<Pixel, SCREEN_PIXELS> m_elements{};

};