#include "pch.h"
#include "Sprite.h"
#include "World.h"


Sprite::Sprite() : color_(1, 1, 1, 1), bitmap_(nullptr)
{
}

Sprite::Sprite(wstring path) : color_(1, 1, 1, 1), bitmap_(nullptr)
{
	SetPath(path);
}

Sprite::Sprite(const Sprite& other)
{
}

Sprite::~Sprite()
{
	delete bitmap_;
}

void Sprite::SetPath(wstring path)
{
	bitmap_ = new Bitmap(const_cast<WCHAR*>(path.c_str()));
}

void Sprite::Render()
{
	if (!get_visible_() || bitmap_ == nullptr) return;
	Entity::Render();


	bitmap_->Render(get_pos_().x, get_pos_().y);
	World::GetInstance().RenderTextureShader(bitmap_->get_index_count_(), bitmap_->get_texture_()->get_texture_());
}