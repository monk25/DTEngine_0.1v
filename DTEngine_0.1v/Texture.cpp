#include "pch.h"
#include "Texture.h"


Texture::Texture() : texture_(nullptr)
{
}


Texture::~Texture()
{
	texture_->Release();
}

ID3D11ShaderResourceView*& Texture::get_texture_()
{
	return texture_;
}

D3DX11_IMAGE_INFO& Texture::get_info_()
{
	return info_;
}