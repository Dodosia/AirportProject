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
	protected:
		//virtual void OnPaint(PaintEventArgs^ e) override;
	private:
		void InitializeComponent(void);

		MaterialTabControl^ tabControl;
		MaterialTabSelector^ tabSelector;
		TabPage^ flightsTab;
		TabPage^ passangersTab;
		TabPage^ boardingPassTab;
		TabPage^ ticketsTab;
		TabPage^ baggageTab;

		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::Button^ flightsButton;
	};
}
