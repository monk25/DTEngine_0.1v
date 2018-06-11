#include "pch.h"
#include "System.h"

#if defined(DEBUG) | defined(_DEBUG)
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdling, int iCmdshow)
#endif
{
	System* system;

	system = new System();

	system->Run();

	delete system;

	return 0;
}