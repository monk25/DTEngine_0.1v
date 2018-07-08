#pragma once
#include "Entity.h"
#include "Bitmap.h"

class Sprite :
	public Entity
{
public:
	Sprite();
	Sprite(wstring path);
	Sprite(const Sprite& other);
	~Sprite();

	void SetPath(wstring path);
	void Render();

	Bitmap* bitmap_;
	D3DXCOLOR color_;
};

