#include "stdafx.h"
#include "Polygon.h"


/* ========================================================================= */
// テストポリゴンメッシュ
// サンプル的な存在…
/* ========================================================================= */
TestPolygonMesh::TestPolygonMesh()
{
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

// ポリゴン数を得る
int TestPolygonMesh::GetPolygonNum()
{
	return m_vertex_stream.size() / 3;
}

// ポリゴンを得る
PolygonRef TestPolygonMesh::GetPolygon(int index)
{
	PolygonRef ref =
	{
		m_vertex_stream.at(index + 0),
		m_vertex_stream.at(index + 1),
		m_vertex_stream.at(index + 2)
	};
}

