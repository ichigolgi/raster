#pragma once
#include "Math.h"
/* ========================================================================= */
/* �J����                                                                    */
/* ========================================================================= */
class Camera
{
public: // �A�N�Z�b�T��񂵂ɂ������̂łƂ肠�������J TODO: �A�N�Z�b�T���
	math::Vector m_eye{};
	math::Vector m_at{};
	math::Vector m_up{};

	math::Matrix m_transform{};

public:
	/* �R���X�g���N�^ */
	Camera()
	{
		m_eye.Set(0.0f, 0.0f, 0.0f, 1.0f);
		m_at.Set(0.0f, 0.0f, 0.0f, 1.0f);
		m_up.Set(0.0f, 1.0f, 0.0f, 1.0f);
	}

	/* �f�X�g���N�^ */
	~Camera() {}

	/* �J�����ϊ��s��𓾂� */
	math::Matrix& GetTransformMatrix();

	/*  */
	/*  */
	/*  */
	/*  */
	/*  */
	/*  */
	/*  */
	/*  */
	/*  */
};

