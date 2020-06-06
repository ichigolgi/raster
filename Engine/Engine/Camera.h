#pragma once
#include "Math.h"
/* ========================================================================= */
/* カメラ                                                                    */
/* ========================================================================= */
class Camera
{
public: // アクセッサ後回しにしたいのでとりあえず公開 TODO: アクセッサ作る
	math::Vector m_eye{};
	math::Vector m_at{};
	math::Vector m_up{};

	math::Matrix m_transform{};

public:
	/* コンストラクタ */
	Camera()
	{
		m_eye.Set(0.0f, 0.0f, 0.0f, 1.0f);
		m_at.Set(0.0f, 0.0f, 0.0f, 1.0f);
		m_up.Set(0.0f, 1.0f, 0.0f, 1.0f);
	}

	/* デストラクタ */
	~Camera() {}

	/* カメラ変換行列を得る */
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

