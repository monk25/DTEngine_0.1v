#pragma once
#include "Define.h"
#include "Singleton.h"
#include "D3D.h"
#include "TextureShader.h"
#include "Scene.h"

class World :
	public Singleton<World>
{
public:
	World();
	World(const World&);
	~World();

	void Initialize(int screenWidth, int screenHeight);
	void Dispose();

	void Render();
	void Update();
	void ChangeScene(Scene* scene);
	int GetKeyState(int vk);
	D3DXVECTOR2 GetMousePos();

	void RenderTextureShader(int index_count, ID3D11ShaderResourceView* texture);

	Scene* get_current_scene_();
	D3D* get_d3d_();
	TextureShader* get_texture_shader_();

private:
	Scene* current_scene_;
	bool current_keys_[256];
	bool last_keys_[256];
	POINT mouse_pos_;

	clock_t start_clock_;
	clock_t current_clock_;
	clock_t last_clock_;
	double dt_;

	D3D* d3d_;
	TextureShader* texture_shader_;
};

