#include "pch.h"
#include "TestScene.h"


TestScene::TestScene()
{
	spr = new Sprite(L"../Resource/seafloor.dds");
	AddChild(spr);

	ani = new Animation(L"../Resource/0", 12, 24);
	ani->SetPos(D3DXVECTOR2(100, 0));
	AddChild(ani);
}


TestScene::~TestScene()
{
}

void TestScene::Render()
{
	Scene::Render();
}

void TestScene::Update(float dt)
{
	Scene::Update(dt);
}