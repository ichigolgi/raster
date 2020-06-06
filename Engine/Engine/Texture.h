#pragma once
#include "stdafx.h"
#include <array>

/* �e�N�X�`�� */
// ���m�ɂ̓o�b�N�o�b�t�@
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
	CTexture() {}
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

	// NOTE: �{���� SCREEN_SIZE_W�Ƃ�����Ȃ��ăT�C�Y���������Ŏ���

private:
	std::array<Pixel, SCREEN_PIXELS> m_elements{};

};