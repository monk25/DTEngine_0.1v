#include "pch.h"
#include "D3D.h"
#include "System.h"


D3D::D3D() :
	swap_chain_(nullptr), device_(nullptr), device_context_(nullptr),
	render_target_view_(nullptr), depth_stencil_buffer_(nullptr),
	depth_stencil_state_(nullptr), depth_stencil_view_(nullptr),
	raster_state_(nullptr), depth_disabled_stencil_state_(nullptr)
{
	Initialize(application_handle_->get_screen_width_(), application_handle_->get_screen_height_(),
		kVsyncEnable, application_handle_->get_hwnd_(), kFullScreen, kScreenDepth, kScreenNear);
}

D3D::D3D(const D3D& other)
{
}

D3D::~D3D()
{
	swap_chain_->SetFullscreenState(false, NULL);
	depth_disabled_stencil_state_->Release();
	raster_state_->Release();
	depth_stencil_view_->Release();
	depth_stencil_state_->Release();
	depth_stencil_buffer_->Release();
	render_target_view_->Release();
	device_context_->Release();
	device_->Release();
	swap_chain_->Release();

	return;
}

bool D3D::Initialize(int screen_width, int screen_height, bool vsync,
	HWND hwnd, bool fullscreen, float screen_depth, float screen_near)
{
	HRESULT result;
	IDXGIFactory* factory;
	IDXGIAdapter* adapter;
	IDXGIOutput* adapter_output;
	unsigned int num_modes, numerator, denominator, string_length;
	DXGI_MODE_DESC* display_mode_list;
	DXGI_ADAPTER_DESC adapter_desc;
	int error;
	DXGI_SWAP_CHAIN_DESC swap_chain_desc;
	D3D_FEATURE_LEVEL feature_level;
	ID3D11Texture2D* back_buffer_ptr;
	D3D11_TEXTURE2D_DESC depth_buffer_desc;
	D3D11_DEPTH_STENCIL_DESC depth_stencil_desc;
	D3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc;
	D3D11_RASTERIZER_DESC raster_desc;
	D3D11_VIEWPORT viewport;
	float field_of_view, screen_aspect;
	D3D11_DEPTH_STENCIL_DESC depth_disabled_stencil_desc;

	vsync_enabled_ = vsync;

	result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(result)) {
		return false;
	}

	result = factory->EnumAdapters(0, &adapter);
	if (FAILED(result)) {
		return false;
	}

	result = adapter->EnumOutputs(0, &adapter_output);
	if (FAILED(result)) {
		return false;
	}

	result = adapter_output->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, NULL);
	if (FAILED(result)) {
		return false;
	}

	display_mode_list = new DXGI_MODE_DESC[num_modes];
	if (!display_mode_list) {
		return false;
	}

	result = adapter_output->GetDisplayModeList(DXGI_FORMAT_R10G10B10A2_UNORM, DXGI_ENUM_MODES_INTERLACED, &num_modes, display_mode_list);
	if (FAILED(result)) {
		return false;
	}

	for (int i = 0; i < num_modes; i++) {
		if (display_mode_list[i].Width == (unsigned int)screen_width) {
			if (display_mode_list[i].Height == (unsigned int)screen_height) {
				numerator = display_mode_list[i].RefreshRate.Numerator;
				denominator = display_mode_list[i].RefreshRate.Denominator;
			}
		}
	}

	result = adapter->GetDesc(&adapter_desc);
	if (FAILED(result)) {
		return false;
	}

	video_card_memory_ = (int)(adapter_desc.DedicatedVideoMemory / 1024 / 1024);

	error = wcstombs_s(&string_length, video_card_description_, 128, adapter_desc.Description, 128);
	if (error != 0) {
		return false;
	}

	delete[] display_mode_list;
	adapter_output->Release();
	adapter->Release();
	factory->Release();

	ZeroMemory(&swap_chain_desc, sizeof(swap_chain_desc));
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.BufferDesc.Width = screen_width;
	swap_chain_desc.BufferDesc.Height = screen_height;
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

	if (vsync_enabled_) {
		swap_chain_desc.BufferDesc.RefreshRate.Numerator = numerator;
		swap_chain_desc.BufferDesc.RefreshRate.Denominator = denominator;
	}
	else {
		swap_chain_desc.BufferDesc.RefreshRate.Numerator = 0;
		swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	}

	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.OutputWindow = hwnd;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;

	if (fullscreen) {
		swap_chain_desc.Windowed = false;
	}
	else {
		swap_chain_desc.Windowed = true;
	}

	swap_chain_desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swap_chain_desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_chain_desc.Flags = 0;

	feature_level = D3D_FEATURE_LEVEL_11_0;
	result = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, &feature_level, 1,
		D3D11_SDK_VERSION, &swap_chain_desc, &swap_chain_, &device_, NULL, &device_context_);
	if (FAILED(result)) {
		return false;
	}

	result = swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&back_buffer_ptr);
	if (FAILED(result)) {
		return false;
	}

	result = device_->CreateRenderTargetView(back_buffer_ptr, NULL, &render_target_view_);
	if (FAILED(result)) {
		return false;
	}

	back_buffer_ptr->Release();

	ZeroMemory(&depth_buffer_desc, sizeof(depth_buffer_desc));
	depth_buffer_desc.Width = screen_width;
	depth_buffer_desc.Height = screen_height;
	depth_buffer_desc.MipLevels = 1;
	depth_buffer_desc.ArraySize = 1;
	depth_buffer_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_buffer_desc.SampleDesc.Count = 1;
	depth_buffer_desc.SampleDesc.Quality = 0;
	depth_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	depth_buffer_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depth_buffer_desc.CPUAccessFlags = 0;
	depth_buffer_desc.MiscFlags = 0;

	result = device_->CreateTexture2D(&depth_buffer_desc, NULL, &depth_stencil_buffer_);
	if (FAILED(result)) {
		return false;
	}

	ZeroMemory(&depth_stencil_desc, sizeof(depth_stencil_desc));
	depth_stencil_desc.DepthEnable = true;
	depth_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depth_stencil_desc.StencilEnable = true;
	depth_stencil_desc.StencilReadMask = 0xFF;
	depth_stencil_desc.StencilWriteMask = 0xFF;
	depth_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depth_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depth_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depth_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = device_->CreateDepthStencilState(&depth_stencil_desc, &depth_stencil_state_);
	if (FAILED(result)) {
		return false;
	}

	device_context_->OMSetDepthStencilState(depth_stencil_state_, 1);

	ZeroMemory(&depth_stencil_view_desc, sizeof(depth_stencil_view_desc));
	depth_stencil_view_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depth_stencil_view_desc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depth_stencil_view_desc.Texture2D.MipSlice = 0;

	result = device_->CreateDepthStencilView(depth_stencil_buffer_, &depth_stencil_view_desc, &depth_stencil_view_);
	if (FAILED(result)) {
		return false;
	}
	device_context_->OMSetRenderTargets(1, &render_target_view_, depth_stencil_view_);
	raster_desc.AntialiasedLineEnable = false;
	raster_desc.CullMode = D3D11_CULL_BACK;
	raster_desc.DepthBias = 0;
	raster_desc.DepthBiasClamp = 0.0f;
	raster_desc.DepthClipEnable = true;
	raster_desc.FillMode = D3D11_FILL_SOLID;
	raster_desc.FrontCounterClockwise = false;
	raster_desc.MultisampleEnable = false;
	raster_desc.ScissorEnable = false;
	raster_desc.SlopeScaledDepthBias = 0.0f;

	result = device_->CreateRasterizerState(&raster_desc, &raster_state_);
	if (FAILED(result)) {
		return false;
	}

	device_context_->RSSetState(raster_state_);

	viewport.Width = (float)screen_width;
	viewport.Height = (float)screen_height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	viewport.TopLeftX = 0.0f;
	viewport.TopLeftY = 0.0f;
	device_context_->RSSetViewports(1, &viewport);

	field_of_view = (float)D3DX_PI / 4.0f;
	screen_aspect = (float)screen_width / (float)screen_height;
	D3DXMatrixPerspectiveFovLH(&projection_matrix_, field_of_view, screen_aspect, screen_near, screen_depth);
	D3DXMatrixIdentity(&world_matrix_);
	D3DXMatrixOrthoLH(&ortho_matrix_, (float)screen_width, (float)screen_height, screen_near, screen_depth);

	ZeroMemory(&depth_disabled_stencil_desc, sizeof(depth_disabled_stencil_desc));

	depth_disabled_stencil_desc.DepthEnable = false;
	depth_disabled_stencil_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depth_disabled_stencil_desc.DepthFunc = D3D11_COMPARISON_LESS;
	depth_disabled_stencil_desc.StencilEnable = true;
	depth_disabled_stencil_desc.StencilReadMask = 0xFF;
	depth_disabled_stencil_desc.StencilWriteMask = 0xFF;
	depth_disabled_stencil_desc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_disabled_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depth_disabled_stencil_desc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_disabled_stencil_desc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depth_disabled_stencil_desc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depth_disabled_stencil_desc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depth_disabled_stencil_desc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depth_disabled_stencil_desc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	result = device_->CreateDepthStencilState(&depth_disabled_stencil_desc, &depth_disabled_stencil_state_);
	if (FAILED(result)) {
		return false;
	}

	return true;
}

void D3D::BeginScene(float red, float green, float blue, float alpha)
{
	float color[4];

	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;

	device_context_->ClearRenderTargetView(render_target_view_, color);
	device_context_->ClearDepthStencilView(depth_stencil_view_, D3D11_CLEAR_DEPTH, 1.0f, 0);

	return;
}

void D3D::EndScene()
{
	if (vsync_enabled_) {
		swap_chain_->Present(1, 0);
	}
	else {
		swap_chain_->Present(0, 0);
	}

	return;
}

ID3D11Device* D3D::get_device_()
{
	return device_;
}

ID3D11DeviceContext* D3D::get_device_context_()
{
	return device_context_;
}

void D3D::get_projection_matrix_(D3DXMATRIX& projection_matrix)
{
	projection_matrix = projection_matrix_;
	return;
}

void D3D::get_world_matrix_(D3DXMATRIX& world_matrix)
{
	world_matrix = world_matrix_;
	return;
}

void D3D::get_ortho_matrix_(D3DXMATRIX& ortho_matrix)
{
	ortho_matrix = ortho_matrix_;
	return;
}

void D3D::get_video_card_info(char* cardName, int& memory)
{
	strcpy_s(cardName, 128, video_card_description_);
	memory = video_card_memory_;
	return;
}

void D3D::TurnZBufferOn()
{
	device_context_->OMSetDepthStencilState(depth_stencil_state_, 1);
}

void D3D::TurnZBufferOff()
{
	device_context_->OMSetDepthStencilState(depth_disabled_stencil_state_, 1);
	return;
}