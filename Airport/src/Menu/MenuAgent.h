#pragma once

#include "BasicForms/Flights.h"
#include "BasicForms/Passangers.h"
#include "BasicForms/BoardingPass.h"
#include "BasicForms/Tickets.h"
#include "BasicForms/Baggage.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace MaterialSkin;
using namespace MaterialSkin::Controls;

namespace Airport 
{
	public ref class MenuAgentForm : public System::Windows::Forms::Form
	{
	public:
		MenuAgentForm(void);
		~MenuAgentForm();
		TabPage^ boardingPassTab;
		TabPage^ baggageTab;
	protected:

	private:
		void InitializeComponent(void);
		void tabControl_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);

		MaterialTabControl^ tabControl;
		MaterialTabSelector^ tabSelector;
		TabPage^ flightsTab;
		TabPage^ passangersTab;
		TabPage^ ticketsTab;

		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::Button^ flightsButton;
	};
}
