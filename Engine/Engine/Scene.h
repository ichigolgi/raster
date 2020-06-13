#pragma once
#include "Polygon.h"
#include <vector>

/**
 * シーン
 * 描画に必要なものを入れておくデータ
 */
struct CScene {
    // ポリゴンデータ
    std::vector<polygon::MeshBase *> polygons;

    //

    // クリア関数
    void Clear() { polygons.clear(); }
};