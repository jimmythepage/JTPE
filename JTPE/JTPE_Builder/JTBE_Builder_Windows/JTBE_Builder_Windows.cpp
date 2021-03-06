#include "JAppPch.h"
#include "JTBE_Builder_Windows.h"


int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	J::APP::JApp app;
	app.Init(APP_NAME_STR);
	app.Activate();
	while (!app.IsReadyToShut())
	{
		app.Update();
	}
	app.Deactivate();
	app.Clear();
	return 0;
}
