#include "pch.h"
#include "TestScene.h"


TestScene::TestScene()
{
	spr = new Sprite(L"../Resource/seafloor.dds");
	//spr->set_pos_(D3DXVECTOR2(1280, 720) / 2);
	AddChild(spr);
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