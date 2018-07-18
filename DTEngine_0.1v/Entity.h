#pragma once
#include "Define.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	virtual void Update(float dt);
	virtual void Render();
	void AddChild(Entity* child);
	void RemoveChild(Entity* child);
	Rect RectWithPos();
	void SetCenter(D3DXVECTOR2 pos);
	D3DXVECTOR2 Center();

	D3DXVECTOR2 GetPos();
	void SetPos(D3DXVECTOR2 pos);

	float GetRotation();
	void SetRotation(float rotation);

	D3DXVECTOR2 GetRotationCenter();
	void SetRotationCenter(D3DXVECTOR2 rotation_center);

	D3DXVECTOR2 GetScale();
	void SetScale(D3DXVECTOR2 scale);

	D3DXVECTOR2 GetScaleCenter();
	void SetScaleCenter(D3DXVECTOR2 scale_center);

	Rect GetRect();
	void SetRect(Rect rect);

	Rect GetVisibleRect();
	void SetVisibleRect(Rect rect);

	bool GetVisible();
	void SetVisible(bool visible);

	bool GetRemoving();

private:
	Entity * parent_;
	vector<Entity*> children_;
	D3DXVECTOR2 pos_;
	float rotation_;
	D3DXVECTOR2 rotation_center_;
	D3DXVECTOR2 scale_;
	D3DXVECTOR2 scale_center_;
	D3DXMATRIX matrix_;
	Rect rect_;
	Rect visible_rect_;
	bool visible_;
	bool update_enabled_;
	bool render_children_enabled_;
	bool removing_;
};

