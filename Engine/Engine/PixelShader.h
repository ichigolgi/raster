#pragma once

// �s�N�Z���V�F�[�_
class CPixelShader {
public:
  struct InPixelShader {};
  struct OutPixelShader {};

  void Run(const InPixelShader &in, OutPixelShader &out) {}
};
