#include "pch.h"
#include "Entity.h"


Entity::Entity() :
	parent_(nullptr), pos_(0.0f, 0.0f), rotation_(0.0f),
	rotation_center_(0.0f, 0.0f), scale_(1.0f, 1.0f),
	scale_center_(0.0f, 0.0f), rect_(0, 0, 0, 0),
	visible_rect_(0, 0, 0, 0), visible_(true),
	update_enabled_(true), render_children_enabled_(true),
	removing_(false)
{
}


Entity::~Entity()
{
	for (auto* child : children_)
		delete child;
}

void Entity::AddChild(Entity* child)
{
	child->parent_ = this;
	children_.push_back(child);
}

void Entity::RemoveChild(Entity* child)
{
	child->removing_ = true;
}

void Entity::Update(float dt)
{
	if (!update_enabled_) return;

	for (auto* child : children_)
		child->Update(dt);

	children_.erase(remove_if(children_.begin(), children_.end(), [](Entity* child) {
		if (child->GetRemoving()) {
			delete child;
			return true;
		}
		return false;
	}), children_.end());
}

void Entity::Render()
{
	if (!visible_) return;
	D3DXMatrixTransformation2D(&matrix_, &scale_center_, 0, &scale_, &rotation_center_, rotation_, &pos_);

	if (parent_)
		matrix_ *= parent_->matrix_;

	if (!render_children_enabled_) return;
	for (auto* child : children_)
		child->Render();
}

D3DXVECTOR2 Entity::Center()
{
	return pos_ + rect_.Center();
}

Rect Entity::RectWithPos()
{
	return rect_.Offset(pos_);
}

void Entity::SetCenter(D3DXVECTOR2 pos)
{
	pos_ = pos - rect_.Center();
}

D3DXVECTOR2 Entity::GetPos()
{
	return pos_;
}

void Entity::SetPos(D3DXVECTOR2 pos)
{
	pos_ = pos;
}

float Entity::GetRotation()
{
	return rotation_;
}

void Entity::SetRotation(float rotation)
{
	rotation_ = rotation;
}

D3DXVECTOR2 Entity::GetRotationCenter()
{
	return rotation_center_;
}

void Entity::SetRotationCenter(D3DXVECTOR2 rotation_center)
{
	rotation_center_ = rotation_center;
}

D3DXVECTOR2 Entity::GetScale()
{
	return scale_;
}

void Entity::SetScale(D3DXVECTOR2 scale)
{
	scale_ = scale;
}

D3DXVECTOR2 Entity::GetScaleCenter()
{
	return scale_center_;
}

void Entity::SetScaleCenter(D3DXVECTOR2 scale_center)
{
	scale_center_ = scale_center;
}

Rect Entity::GetRect()
{
	return rect_;
}

void Entity::SetRect(Rect rect)
{
	rect_ = rect;
}

Rect Entity::GetVisibleRect()
{
	return visible_rect_;
}

void Entity::SetVisibleRect(Rect rect)
{
	visible_rect_ = rect;
}

bool Entity::GetVisible()
{
	return visible_;
}

void Entity::SetVisible(bool visible)
{
	visible_ = visible;
}

bool Entity::GetRemoving()
{
	return removing_;
}