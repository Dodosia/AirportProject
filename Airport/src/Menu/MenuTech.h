#pragma once

#include "BasicForms/DepartureBoard.h"
#include "BasicForms/ArrivalBoard.h"
#include "BasicForms/Airplanes.h"
#include "BasicForms/Airports.h"
#include "BasicForms/TechFlightsForm.h"

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
	public ref class MenuTechForm : public System::Windows::Forms::Form
	{
	public:
		MenuTechForm(void);
		~MenuTechForm();
		TabPage^ airplaneTab;
	protected:
		//virtual void OnPaint(PaintEventArgs^ e) override;
	private:
		void InitializeComponent(void);

		MaterialTabControl^ tabControl;
		MaterialTabSelector^ tabSelector;

		TabPage^ flightsTab;
		TabPage^ depBoardTab;
		TabPage^ arBoardTab;


		System::ComponentModel::IContainer^ components;
		System::Windows::Forms::Button^ flightsButton;
	};
}