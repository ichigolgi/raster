#pragma once

// ���_�V�F�[�_
class CVertexShader {
   public:
    struct InVertexShader {};
    struct OutVertexShader {};

    void Run(const InVertexShader &in, OutVertexShader &out) {}
};
