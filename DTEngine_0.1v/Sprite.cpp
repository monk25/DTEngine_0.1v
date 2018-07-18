#include "pch.h"
#include "Sprite.h"
#include "World.h"
#include "Asset.h"


Sprite::Sprite() : color_(1, 1, 1, 1), texture_(nullptr)
{
}

Sprite::Sprite(wstring path) : color_(1, 1, 1, 1), texture_(nullptr)
{
	SetPath(path);
}


Sprite::~Sprite()
{
	delete texture_;
}

void Sprite::SetPath(wstring path)
{
	texture_ = Asset::GetInstance().GetTexture(path);
	SetRect(Rect(0, 0, texture_->GetInfo().Width, texture_->GetInfo().Height));
}

void Sprite::Render()
{
	if (!GetVisible() || texture_ == nullptr) return;
	Entity::Render();

	World::GetInstance().GetBitmap()->Render(this);
	World::GetInstance().RenderTextureShader(texture_->GetIndexCount(), texture_->GetTexture());
}

Texture* Sprite::GetTexture()
{
	return texture_;
}

void Sprite::SetTexture(Texture* texture)
{
	texture_ = texture;
}