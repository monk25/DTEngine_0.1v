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

	D3DXVECTOR2 get_pos_();
	void set_pos_(D3DXVECTOR2 pos);

	float get_rotation_();
	void set_rotation_(float rotation);

	D3DXVECTOR2 get_rotation_center_();
	void set_rotation_center(D3DXVECTOR2 rotation_center);

	D3DXVECTOR2 get_scale_();
	void set_scale_(D3DXVECTOR2 scale);

	D3DXVECTOR2 get_scale_center_();
	void set_scale_center_(D3DXVECTOR2 scale_center);

	Rect get_rect_();
	void set_rect_(Rect rect);

	Rect get_visible_rect_();
	void set_visible_rect_(Rect rect);

	bool get_visible_();
	void set_visible_(bool visible);

	bool get_removing_();

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

