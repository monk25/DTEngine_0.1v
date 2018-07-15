#pragma once
#include "Entity.h"
#include "Camera.h"

class Scene :
	public Entity
{
public:
	Scene();
	~Scene();

	void Update(float dt);
	void Follow(Entity* target, D3DXVECTOR2 offset);
	void UnFollow();
	void Shake(int cnt, float range, float duration);

	Camera* get_camera_();
	
private:
	Entity* follow_target_;
	D3DXVECTOR2 offset_;
	Camera* camera_;
};

