#pragma once
#include "Define.h"

class Texture
{
public:
	Texture();
	Texture(const Texture&);
	~Texture();

	ID3D11ShaderResourceView* texture_;
	D3DX11_IMAGE_LOAD_INFO info_;
};

