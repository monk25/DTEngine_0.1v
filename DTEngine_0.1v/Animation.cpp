#include "pch.h"
#include "Animation.h"
#include "Asset.h"


Animation::Animation(const wstring& path, int frame_num, float fps, bool loop)
	:current_frame_(0), fps_(fps), loop_(loop)
{
	for (int i = 0; i < frame_num; i++) {
		Texture* t = Asset::GetInstance().GetTexture(path + L"/" + to_wstring(i) + L".png");
		textures_.push_back(t);
	}
	//texture_ = textures_[0];
}


Animation::~Animation()
{
}

void Animation::Update(float dt)
{
	Sprite::Update(dt);
}