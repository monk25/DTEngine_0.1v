#pragma once
#define WIN32_LEAN_AND_MEAN
#include "Define.h"

class System
{
public:
	System();
	System(const System&);
	~System();

	void Run();

	LRESULT CALLBACK MessageHandle(HWND, UINT, WPARAM, LPARAM);

	int get_screen_width_();
	void set_screen_width_(int screen_width);

	int get_screen_height_();
	void set_screen_height_(int screen_width);

	HWND get_hwnd_();

private:
	bool Frame();
	void InitializeWindows();
	void ShutdownWindows();

private:
	LPCWSTR application_name_;
	HINSTANCE hinstance_;
	HWND hwnd_;

	int screen_width_, screen_height_;
};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
extern System * application_handle_;