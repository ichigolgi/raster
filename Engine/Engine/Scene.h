#pragma once
#include <vector>
#include "Polygon.h"

/**
* �V�[��
* �`��ɕK�v�Ȃ��̂����Ă����f�[�^
*/
struct CScene
{
	// �|���S���f�[�^
	std::vector<Polygon::PolygonBase*> polygons;

	// 


	// �N���A�֐�
	void Clear()
	{
		polygons.clear();
	}
};