#include "Main_Form.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	PathfindingForm::Main_Form form;
	Application::Run(%form);
	return 0;
}// main

