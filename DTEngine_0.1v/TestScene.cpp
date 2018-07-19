#include "pch.h"
#include "TestScene.h"


TestScene::TestScene()
{
	spr = new Sprite(L"../Resource/seafloor.dds");
	spr->SetPosition(D3DXVECTOR3(50, 0, 0));
	AddChild(spr);

	ani = new Animation(L"../Resource/0", 12, 24);
	ani->SetPosition(D3DXVECTOR3(0, 0, 0));
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
	D3DXVECTOR3 rotation = spr->GetRotation();
	rotation.z += dt * 90.0f;
	D3DXVECTOR3 scale = spr->GetScale();
	scale.x += dt * 1.0f;
	spr->SetRotation(rotation);
	spr->SetScale(scale);
}