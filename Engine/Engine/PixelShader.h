#pragma once

// ピクセルシェーダ
class CPixelShader {
public:
  struct InPixelShader {};
  struct OutPixelShader {};

  void Run(const InPixelShader &in, OutPixelShader &out) {}
};
