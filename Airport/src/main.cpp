#include "LoginForm.h"
#include "BasicForms/Flights.h"
#include "Menu/MenuAgent.h"

using namespace System;
using namespace System::Windows::Forms;

int main(array<String^>^ args)
{
    Application::SetCompatibleTextRenderingDefault(false);
    Application::EnableVisualStyles();
    Airport::EntryPoint form;
    Application::Run(% form);
}


