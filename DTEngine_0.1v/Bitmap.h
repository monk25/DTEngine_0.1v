#pragma once
#include "Define.h"
#include "Texture.h"

class Bitmap
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
public:
	Bitmap(WCHAR*);
	~Bitmap();

	void Render(int, int);

	int get_index_count_();
	Texture* get_texture_();

private:
	void InitializeBuffers();
	void ShutdownBuffers();
	void UpdateBuffers(int, int);
	void RenderBuffers();

	void LoadTexture(WCHAR*);

private:
	ID3D11Buffer* vertex_buffer_, * index_buffer_;
	int vertex_count_, index_count_;

	int screen_width_, screen_height_;
	int bitmap_width_, bitmap_height_;
	int previous_pos_x_, previous_pos_y_;

private:
	Texture * texture_;
};

