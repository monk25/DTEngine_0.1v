#pragma once
#include "pch.h"

#if defined(DEBUG) | defined(_DEBUG)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

const int kScreenWidth = 1280;
const int kScreenHeight = 720;
const bool kFullScreen = false;
const bool kVsyncEnable = true;
const float kScreenDepth = 1000.0f;
const float kScreenNear = 0.1f;

class Rect :
	public RECT
{
public:
	Rect() {
		left = top = right = bottom = 0;
	}

	Rect(int left, int top, int right, int bottom) {
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}

	bool IntersectsRect(Rect rect) {
		Rect tmpRect;
		return IntersectRect(&tmpRect, this, &rect);
	}

	bool IntersectsRect(Rect rect, D3DXVECTOR2 pos) {
		Rect tmpRect;
		return IntersectRect(&tmpRect, this, &rect.Offset(pos));
	}

	Rect Offset(D3DXVECTOR2 pos) {
		Rect r = *this;
		r.left += pos.x;
		r.top += pos.y;
		r.right += pos.x;
		r.bottom += pos.y;
		return r;
	}

	int Width() {
		return right - left;
	}

	int Height() {
		return bottom - top;
	}

	D3DXVECTOR2 Center() {
		return D3DXVECTOR2(Width(), Height()) / 2;
	}
};

inline float Pita(D3DXVECTOR2 v1, D3DXVECTOR2 v2)
{
	return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

inline float Angle(D3DXVECTOR2 v1, D3DXVECTOR2 v2)
{
	return atan2(v2.y - v1.y, v2.x - v1.x);
}

inline int Random(int from, int to)
{
	static default_random_engine d(timeGetTime());
	uniform_int_distribution<int> random(from, to);
	return random(d);
}

inline float Random(float from, float to)
{
	static default_random_engine d(timeGetTime());
	uniform_real_distribution<float> random(from, to);
	return random(d);
}