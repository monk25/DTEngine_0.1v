#pragma once
#include "Scene.h"
#include "Sprite.h"

class TestScene :
	public Scene
{
public:
	TestScene();
	~TestScene();

	void Render();
	void Update(float dt);

	Sprite* spr;
};

