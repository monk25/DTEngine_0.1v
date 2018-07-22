#include "pch.h"
#include "TestScene.h"
#include "World.h"


TestScene::TestScene()
{
	spr = new Sprite(L"../Resource/seafloor.dds");
	spr->SetPosition(D3DXVECTOR3(0, 0, 0));
	AddChild(spr);

	ani = new Animation(L"../Resource/0", 12, 24);
	ani->SetPosition(D3DXVECTOR3(0, 0, 0));
	ani->SetLightEnabled(true);
	AddChild(ani);

	Follow(spr);
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

	D3DXVECTOR3 pos = spr->GetPosition();

	if (World::GetInstance().GetKeyState(VK_LEFT) > 0) {
		pos.x -= 500.0f * dt;
	}
	if (World::GetInstance().GetKeyState(VK_RIGHT) > 0) {
		pos.x += 500.0f * dt;
	}
	if (World::GetInstance().GetKeyState(VK_UP) > 0) {
		pos.y += 500.0f * dt;
	}
	if (World::GetInstance().GetKeyState(VK_DOWN) > 0) {
		pos.y -= 500.0f * dt;
	}

	if (World::GetInstance().GetKeyState(VK_RETURN) > 0) {
		Shake(10, 20, 0.01f);
	}

	if (World::GetInstance().GetKeyState(VK_LBUTTON) > 0)
	{
		static D3DXVECTOR2 curMousePos, oldMousePos;

		if (World::GetInstance().GetKeyState(VK_LBUTTON) == 1)
		{
			curMousePos = World::GetInstance().GetMousePos();
			oldMousePos = curMousePos;
		}

		oldMousePos = curMousePos;
		curMousePos = World::GetInstance().GetMousePos();

		GetCamera()->SetPosition(GetCamera()->GetPosition().x - (curMousePos.x - oldMousePos.x), GetCamera()->GetPosition().y + (curMousePos.y - oldMousePos.y), GetCamera()->GetPosition().z);
	}

	if (World::GetInstance().GetKeyState('Q') == 2)
	{
		std::cout << GetLight()->GetDirection().z << std::endl;
		GetLight()->SetDirection(GetLight()->GetDirection().x, GetLight()->GetDirection().y, GetLight()->GetDirection().z + 3.0f * dt);
	}
	if (World::GetInstance().GetKeyState('E') == 2)
	{
		std::cout << GetLight()->GetDirection().z << std::endl;
		GetLight()->SetDirection(GetLight()->GetDirection().x, GetLight()->GetDirection().y, GetLight()->GetDirection().z - 3.0f * dt);
	}

	spr->SetPosition(pos);
}