#pragma once

// 頂点シェーダ
class CVertexShader {
   public:
    struct InVertexShader {};
    struct OutVertexShader {};

    void Run(const InVertexShader &in, OutVertexShader &out) {}
};
