#pragma once
#include "Entity.h"
#include "Texture.h"

class Sprite :
	public Entity
{
public:
	Sprite();
	Sprite(wstring path);
	~Sprite();

	void SetPath(wstring path);
	void Render();

	Texture* GetTexture();
	void SetTexture(Texture* texture);

private:
	Texture* texture_;
	D3DXCOLOR color_;
};

