#pragma once
#include <array>
#include <cassert>

namespace math {

/* ========================================================================= */
/* �x�N�g��                                                                  */
/* ========================================================================= */
class Vector {
  enum { ELEMENT_NUM = 4 };
  std::array<float, ELEMENT_NUM> m_element;

public:
  float &X() { return m_element.at(0); }
  float &Y() { return m_element.at(1); }
  float &Z() { return m_element.at(2); }
  float &W() { return m_element.at(3); }

  float &Get(int index) { return m_element.at(index); }

  void Set(float x, float y, float z, float w) {
    m_element.at(0) = x;
    m_element.at(1) = y;
    m_element.at(2) = z;
    m_element.at(3) = w;
  }
};

/* ========================================================================= */
/* �s��                                                                      */
/* ========================================================================= */
class Matrix {
  enum { ELEMENT_NUM = 4 };
  std::array<math::Vector, ELEMENT_NUM> m_element;

public:
  Vector &X() { return m_element.at(0); }
  Vector &Y() { return m_element.at(1); }
  Vector &Z() { return m_element.at(2); }
  Vector &W() { return m_element.at(3); }

  Vector &Get(int index) { return m_element.at(index); }

  void Set(int index, float x, float y, float z, float w) {
    m_element.at(index).Set(x, y, z, w);
  }
};

/* ========================================================================= */
/* �x�N�g�����m�̉��Z                                                        */
/* ========================================================================= */

/* ========================================================================= */
/* �s�񓯎m�̉��Z                                                            */
/* ========================================================================= */

/* ========================================================================= */
/* �x�N�g���ƍs��̉��Z                                                      */
/* ========================================================================= */

} // namespace math
