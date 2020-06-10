#pragma once
#include "Math.h"
#include <vector>
#include <tuple>

/* ========================================================================= */
// ポリゴン
/* ========================================================================= */
typedef math::Vector Vertex;
typedef std::vector<Vertex> VertexSteam;
typedef std::tuple<Vertex, Vertex, Vertex> Polygon;
typedef std::tuple<Vertex&, Vertex&, Vertex&> PolygonRef;


/* ========================================================================= */
// ポリゴンメッシュベース
/* ========================================================================= */
class PolygonMeshBase {
public:
  enum class VertexType {
    TRIANGLE_LIST,
    TRIANGLE_STRIP,
  };
  typedef math::Vector Vertex;
  typedef std::vector<Vertex> VertexSteam;

public:
	PolygonMeshBase() {}
  virtual ~PolygonMeshBase(){};

  // アクセッサがより簡単になるように修正中
  // それいかんによってはこの関数消すかも
  //
  // 頂点リスト取得
  // 継承したクラスたちは m_vertex_stream, m_vertex_type
  // を自分の好きなように生成する
  //const VertexSteam &GetVertexStream() { return m_vertex_stream; }

  // ポリゴン数を得る
  virtual int GetPolygonNum() = 0;

  // ポリゴンを得る
  virtual PolygonRef GetPolygon(int index) = 0;

protected:
  // std::vector<int> m_index_stream{}; // インデクスリスト // イランノデハ？
  VertexSteam m_vertex_stream{};                       // 頂点リスト
  VertexType m_vertex_type{VertexType::TRIANGLE_LIST}; // 頂点タイプ
};

/* ========================================================================= */
// テストポリゴンメッシュ
// サンプル的な存在…
/* ========================================================================= */
class TestPolygonMesh : public PolygonMeshBase {
public:
  typedef PolygonMeshBase BaseType;

public:

	TestPolygonMesh();
  virtual ~TestPolygonMesh(){};

  // ポリゴン数を得る
  int GetPolygonNum() override;

  // ポリゴンを得る
  PolygonRef GetPolygon(int index) override;
};
