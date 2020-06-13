#pragma once
#include "Math.h"
#include <vector>
#include <tuple>

namespace polygon {

/* ========================================================================= */
// �|���S��
/* ========================================================================= */
typedef math::Vector Vertex;
typedef std::vector<Vertex> VertexSteam;
typedef std::tuple<Vertex, Vertex, Vertex> Polygon;
typedef std::tuple<Vertex&, Vertex&, Vertex&> PolygonRef;

/* ========================================================================= */
// �|���S�����b�V���x�[�X
/* ========================================================================= */
class MeshBase {
   public:
    enum class VertexType {
        TRIANGLE_LIST,
        TRIANGLE_STRIP,
    };
    typedef math::Vector Vertex;
    typedef std::vector<Vertex> VertexSteam;

   public:
    MeshBase() {}
    virtual ~MeshBase(){};

    // �A�N�Z�b�T�����ȒP�ɂȂ�悤�ɏC����
    // ���ꂢ����ɂ���Ă͂��̊֐���������
    //
    // ���_���X�g�擾
    // �p�������N���X������ m_vertex_stream, m_vertex_type
    // �������̍D���Ȃ悤�ɐ�������
    // const VertexSteam &GetVertexStream() { return m_vertex_stream; }

    // �|���S�����𓾂�
    virtual int GetPolygonNum() = 0;

    // �|���S���𓾂�
    virtual PolygonRef GetPolygon(int index) = 0;

   protected:
    // std::vector<int> m_index_stream{}; // �C���f�N�X���X�g // �C�����m�f�n�H
    VertexSteam m_vertex_stream{};                        // ���_���X�g
    VertexType m_vertex_type{VertexType::TRIANGLE_LIST};  // ���_�^�C�v
};

/* ========================================================================= */
// �e�X�g�|���S�����b�V��
// �T���v���I�ȑ��݁c
/* ========================================================================= */
class TestMesh : public MeshBase {
   public:
    typedef MeshBase BaseType;

   public:
    TestMesh();
    virtual ~TestMesh(){};

    // �|���S�����𓾂�
    int GetPolygonNum() override;

    // �|���S���𓾂�
    PolygonRef GetPolygon(int index) override;
};

}  // namespace polygon
