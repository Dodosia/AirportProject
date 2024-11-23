#pragma once

#include "BasicForms/Flights.h"
#include "BasicForms/DepartureBoard.h"
#include "BasicForms/ArrivalBoard.h"
#include "BasicForms/Airports.h"

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
	public ref class MenuDispForm : public System::Windows::Forms::Form
	{
	public:
		MenuDispForm(void);
		~MenuDispForm();
	protected:
		//virtual void OnPaint(PaintEventArgs^ e) override;
	private:
		void InitializeComponent(void);

		MaterialTabControl^ tabControl;
		MaterialTabSelector^ tabSelector;

		TabPage^ flightsTab;
		TabPage^ depBoardTab;
		TabPage^ arBoardTab;
		TabPage^ airportTab;

		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::Button^ flightsButton;
	};
}