#include "pch.h"
#include "World.h"
#include "Asset.h"
#include "System.h"
#include "TestScene.h"


World::World()
{
}

World::World(const World& other)
{
}

World::~World()
{
}

void World::Initialize(int screenWidth, int screenHeight)
{
	Asset::GetInstance().Initialize();
	cout.precision(3);
	ZeroMemory(current_keys_, sizeof(current_keys_));
	ZeroMemory(last_keys_, sizeof(last_keys_));
	start_clock_ = current_clock_ = last_clock_ = clock();
	d3d_ = new D3D();
	texture_shader_ = new TextureShader();
	ChangeScene(new TestScene());
}

void World::Dispose()
{
	Asset::GetInstance().Dispose();
}

void World::Render()
{
	D3DXMATRIX world_matrix, view_matrix, projection_matrix, ortho_matrix;

	d3d_->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
	current_scene_->get_camera_()->Render();

	view_matrix = current_scene_->get_camera_()->get_view_matrix_();
	world_matrix = d3d_->get_world_matrix_();
	projection_matrix = d3d_->get_projection_matrix_();
	ortho_matrix = d3d_->get_ortho_matrix_();

	d3d_->TurnZBufferOff();
	current_scene_->Render();
	d3d_->TurnZBufferOn();
	d3d_->EndScene();
}

void World::Update()
{
	last_clock_ = current_clock_;
	current_clock_ = clock();
	dt_ = (float)(current_clock_ - last_clock_) / CLOCKS_PER_SEC;

	for (int i = 0; i < 256; i++) {
		last_keys_[i] = current_keys_[i];
		current_keys_[i] = GetAsyncKeyState(i) & 0x8000;
	}

	GetCursorPos(&mouse_pos_);
	ScreenToClient(application_handle_->get_hwnd_(), &mouse_pos_);
}

void World::ChangeScene(Scene* scene)
{
	if (current_scene_) delete current_scene_;
	current_scene_ = scene;
}

int World::GetKeyState(int vk)
{
	if (current_keys_[vk] && last_keys_[vk]) return 2;
	if (current_keys_[vk] && !last_keys_[vk]) return 1;
	if (!current_keys_[vk] && last_keys_[vk]) return -1;
	return -2;
}

D3DXVECTOR2 World::GetMousePos()
{
	return D3DXVECTOR2(mouse_pos_.x, mouse_pos_.y);
}

void World::RenderTextureShader(int index_count, ID3D11ShaderResourceView* texture)
{
	texture_shader_->Render(index_count, d3d_->get_world_matrix_(), current_scene_->get_camera_()->get_view_matrix_(), d3d_->get_ortho_matrix_(), texture);
}

Scene* World::get_current_scene_()
{
	return current_scene_;
}

D3D* World::get_d3d_()
{
	return d3d_;
}

TextureShader* World::get_texture_shader_()
{
	return texture_shader_;
}