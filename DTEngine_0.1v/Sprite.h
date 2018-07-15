#pragma once
#include "Entity.h"
#include "Bitmap.h"

class Sprite :
	public Entity
{
public:
	Sprite();
	Sprite(wstring path);
	~Sprite();

	void SetPath(wstring path);
	void Render();

private:
	Bitmap* bitmap_;
	D3DXCOLOR color_;
};

