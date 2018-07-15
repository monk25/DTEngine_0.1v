#include "pch.h"
#include "Scene.h"


Scene::Scene() : follow_target_(nullptr), camera_(nullptr)
{
	camera_ = new Camera();
	camera_->SetPosition(0.0f, 0.0f, -5.0f);
}


Scene::~Scene()
{
	delete camera_;
}

void Scene::Update(float dt)
{
	Entity::Update(dt);

	D3DXVECTOR2 target_pos = D3DXVECTOR2(0.0f, 0.0f);

	if (follow_target_) {
		target_pos = -follow_target_->Center();
	}

	D3DXVECTOR2 camera_pos = D3DXVECTOR2(camera_->GetPosition().x, camera_->GetPosition().y);
	D3DXVECTOR2 p = (target_pos + offset_ - camera_pos) * 0.15f + camera_pos;
	camera_->SetPosition(p.x, p.y, camera_->GetPosition().z);
}

void Scene::Follow(Entity* target, D3DXVECTOR2 offset)
{
	follow_target_ = target;
	offset_ = offset;
}

void Scene::UnFollow()
{
	follow_target_ = nullptr;
	offset_ = D3DXVECTOR2(0.0f, 0.0f);
}

void Scene::Shake(int cnt, float range, float duration)
{

}

Camera* Scene::get_camera_()
{
	return camera_;
}