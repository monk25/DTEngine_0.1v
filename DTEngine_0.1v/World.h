#pragma once
#include "Define.h"
#include "Singleton.h"
#include "D3D.h"
#include "TextureShader.h"
#include "Bitmap.h"
#include "Scene.h"
#include "Timer.h"

class World :
	public Singleton<World>
{
public:
	World();
	~World();

	void Initialize(int screenWidth, int screenHeight);
	void Dispose();

	void Render();
	void Update();
	void ChangeScene(Scene* scene);
	int GetKeyState(int vk);
	D3DXVECTOR2 GetMousePos();

	void RenderTextureShader(int index_count, ID3D11ShaderResourceView* texture);

	Scene* GetCurrentScene();
	D3D* GetD3D();
	Bitmap* GetBitmap();
	TextureShader* GetTextureShader();

private:
	Scene* current_scene_;
	bool current_keys_[256];
	bool last_keys_[256];
	POINT mouse_pos_;

	clock_t start_clock_;
	clock_t current_clock_;
	clock_t last_clock_;
	double dt_;

	vector<Timer*> timers;
	D3D* d3d_;
	Bitmap* bitmap_;
	TextureShader* texture_shader_;
};

