#pragma once
#include "Polygon.h"
#include <vector>

/**
 * �V�[��
 * �`��ɕK�v�Ȃ��̂����Ă����f�[�^
 */
struct CScene {
  // �|���S���f�[�^
  std::vector<Polygon::PolygonBase *> polygons;

  //

  // �N���A�֐�
  void Clear() { polygons.clear(); }
};