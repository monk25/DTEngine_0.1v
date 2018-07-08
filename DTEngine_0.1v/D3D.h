#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#include <DXGI.h>
#include <D3Dcommon.h>
#include <D3D11.h>
#include <D3DX10math.h>

class D3D
{
public:
	D3D();
	D3D(const D3D&);
	~D3D();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D11Device* get_device_();
	ID3D11DeviceContext* get_device_context_();

	D3DXMATRIX get_projection_matrix_();
	D3DXMATRIX get_world_matrix_();
	D3DXMATRIX get_ortho_matrix_();

	void get_video_card_info(char*, int&);

	void TurnZBufferOn();
	void TurnZBufferOff();

private:
	bool Initialize(int, int, HWND);

private:
	bool vsync_enabled_;
	int video_card_memory_;
	char video_card_description_[128];
	IDXGISwapChain* swap_chain_;
	ID3D11Device* device_;
	ID3D11DeviceContext* device_context_;
	ID3D11RenderTargetView* render_target_view_;
	ID3D11Texture2D* depth_stencil_buffer_;
	ID3D11DepthStencilState* depth_stencil_state_;
	ID3D11DepthStencilView* depth_stencil_view_;
	ID3D11RasterizerState* raster_state_;
	D3DXMATRIX projection_matrix_;
	D3DXMATRIX world_matrix_;
	D3DXMATRIX ortho_matrix_;
	ID3D11DepthStencilState* depth_disabled_stencil_state_;
};

