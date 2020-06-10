#pragma once
#include "Math.h"
#include <vector>

namespace Polygon {

/* ========================================================================= */
// ポリゴン
/* ========================================================================= */
class PolygonBase {
public:
  enum class VertexType {
    TRIANGLE_LIST,
    TRIANGLE_STRIP,
  };
  typedef math::Vector Vertex;
  typedef std::vector<Vertex> VertexSteam;

public:
  PolygonBase() {}
  virtual ~PolygonBase(){};

  /* 頂点リスト取得 */
  // 継承したクラスたちは m_vertex_stream, m_vertex_type
  // を自分の好きなように生成する
  const VertexSteam &GetVertexStream() { return m_vertex_stream; }

protected:
  // std::vector<int> m_index_stream{}; // インデクスリスト // イランノデハ？
  VertexSteam m_vertex_stream{};                       // 頂点リスト
  VertexType m_vertex_type{VertexType::TRIANGLE_LIST}; // 頂点タイプ
};

/* ========================================================================= */
// テストポリゴン
// サンプル的な存在…
/* ========================================================================= */
class TestPolygon : public PolygonBase {
public:
  typedef PolygonBase BaseType;

private:
  TestPolygon() {}

public:
  TestPolygon() {
    m_vertex_type = VertexType::TRIANGLE_LIST;

    Vertex v0, v1, v2;
    v0.Set(10.f, 0.f, 0.f, 0.f);
    v1.Set(0.f, 10.f, 0.f, 0.f);
    v2.Set(-10.f, 0.f, 0.f, 0.f);
    m_vertex_stream.emplace_back(v0);
    m_vertex_stream.emplace_back(v1);
    m_vertex_stream.emplace_back(v2);
    v0.Set(-10.f, 0.f, 0.f, 0.f);
    v1.Set(0.f, 10.f, 0.f, 0.f);
    v2.Set(10.f, 0.f, 0.f, 0.f);
    m_vertex_stream.emplace_back(v0);
    m_vertex_stream.emplace_back(v1);
    m_vertex_stream.emplace_back(v2);
  }
  virtual ~TestPolygon(){};
}

} // namespace Polygon
