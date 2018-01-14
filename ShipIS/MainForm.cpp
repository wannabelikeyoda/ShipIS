#include "stdafx.h"
#include "MainForm.h"

using namespace ShipIS;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	FreeConsole();
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MainForm());
	return 0;
}