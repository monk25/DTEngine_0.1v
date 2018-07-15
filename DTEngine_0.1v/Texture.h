#pragma once
#include "Define.h"

class Texture
{
public:
	Texture();
	~Texture();

	ID3D11ShaderResourceView*& get_texture_();
	D3DX11_IMAGE_INFO& get_info_();

public:
	ID3D11ShaderResourceView* texture_;
	D3DX11_IMAGE_INFO info_;
};

