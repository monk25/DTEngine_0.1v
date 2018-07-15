#include "pch.h"
#include "Bitmap.h"
#include "World.h"
#include "Asset.h"


Bitmap::Bitmap(WCHAR* texture_filename) : bitmap_width_(0), bitmap_height_(0),
previous_pos_x_(-1), previous_pos_y_(-1)
{
	InitializeBuffers();
	LoadTexture(texture_filename);
	bitmap_width_ = texture_->get_info_().Width;
	bitmap_height_ = texture_->get_info_().Height;
}


Bitmap::~Bitmap()
{
}

void Bitmap::Render(int position_x, int position_y)
{
	UpdateBuffers(position_x, position_y);
	RenderBuffers();
}

int Bitmap::get_index_count_()
{
	return index_count_;
}

void Bitmap::InitializeBuffers()
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertex_buffer_desc, index_buffer_desc;
	D3D11_SUBRESOURCE_DATA vertex_data, index_data;
	HRESULT result;

	vertex_count_ = 6;
	index_count_ = vertex_count_;

	vertices = new VertexType[vertex_count_];
	indices = new unsigned long[index_count_];

	memset(vertices, 0, (sizeof(VertexType) * vertex_count_));

	for (int i = 0; i < index_count_; i++) {
		indices[i] = i;
	}

	vertex_buffer_desc.Usage = D3D11_USAGE_DYNAMIC;
	vertex_buffer_desc.ByteWidth = sizeof(VertexType) * vertex_count_;
	vertex_buffer_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertex_buffer_desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertex_buffer_desc.MiscFlags = 0;
	vertex_buffer_desc.StructureByteStride = 0;

	vertex_data.pSysMem = vertices;
	vertex_data.SysMemPitch = 0;
	vertex_data.SysMemSlicePitch = 0;

	ID3D11Device* device = World::GetInstance().get_d3d_()->get_device_();
	device->CreateBuffer(&vertex_buffer_desc, &vertex_data, &vertex_buffer_);

	index_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	index_buffer_desc.ByteWidth = sizeof(unsigned long) * index_count_;
	index_buffer_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	index_buffer_desc.CPUAccessFlags = 0;
	index_buffer_desc.MiscFlags = 0;
	index_buffer_desc.StructureByteStride = 0;

	index_data.pSysMem = indices;
	index_data.SysMemPitch = 0;
	index_data.SysMemSlicePitch = 0;

	device->CreateBuffer(&index_buffer_desc, &index_data, &index_buffer_);

	delete[] vertices;

	delete[] indices;
}

void Bitmap::ShutdownBuffers()
{
	index_buffer_->Release();
	vertex_buffer_->Release();
}

void Bitmap::UpdateBuffers(int position_x, int position_y)
{
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mapped_resource;
	VertexType* vertices_ptr;

	if ((position_x == previous_pos_x_) && (position_y == previous_pos_y_)) {
		return;
	}

	previous_pos_x_ = position_x;
	previous_pos_y_ = position_y;

	left = (float)((kScreenWidth / 2) * -1) + (float)position_x;
	right = left + (float)bitmap_width_;
	top = (float)(kScreenHeight / 2) - (float)position_y;
	bottom = top - (float)bitmap_height_;

	vertices = new VertexType[vertex_count_];

	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[1].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);
	vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);
	vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[5].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);

	ID3D11DeviceContext* device_context = World::GetInstance().get_d3d_()->get_device_context_();
	device_context->Map(vertex_buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped_resource);

	vertices_ptr = (VertexType*)mapped_resource.pData;
	memcpy(vertices_ptr, (void*)vertices, (sizeof(VertexType) * vertex_count_));
	device_context->Unmap(vertex_buffer_, 0);

	delete[] vertices;

	return;
}

void Bitmap::RenderBuffers()
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	ID3D11DeviceContext* device_context = World::GetInstance().get_d3d_()->get_device_context_();
	device_context->IASetVertexBuffers(0, 1, &vertex_buffer_, &stride, &offset);
	device_context->IASetIndexBuffer(index_buffer_, DXGI_FORMAT_R32_UINT, 0);
	device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Bitmap::LoadTexture(WCHAR* filename)
{
	texture_ = Asset::GetInstance().GetTexture(filename);
}

Texture* Bitmap::get_texture_()
{
	return texture_;
}