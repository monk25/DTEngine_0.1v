#include "pch.h"
#include "System.h"
#include "World.h"

#if defined(DEBUG) | defined(_DEBUG)
int main()
#else
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdling, int iCmdshow)
#endif
{
	System* system;

	system = new System();

	World::GetInstance().Initialize(1280, 720);

	system->Run();

	World::GetInstance().Dispose();

	delete system;

	return 0;
}