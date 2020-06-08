#pragma once
#include <vector>
#include "Polygon.h"

/**
* シーン
* 描画に必要なものを入れておくデータ
*/
struct CScene
{
	// ポリゴンデータ
	std::vector<Polygon::PolygonBase*> polygons;

	// 


	// クリア関数
	void Clear()
	{
		polygons.clear();
	}
};