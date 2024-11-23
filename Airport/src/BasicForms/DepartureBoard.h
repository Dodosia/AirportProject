#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Data::SqlClient;
using namespace MaterialSkin;
using namespace MaterialSkin::Controls;

namespace Airport 
{
	public ref class DepartureBoardForm : public System::Windows::Forms::Form
	{
	public:
		DepartureBoardForm();
		~DepartureBoardForm();
	private:
		void InitializeComponent(void);
		void LoadFlights();

		MaterialSingleLineTextField^ txtFlight;
		MaterialFlatButton^ btnSearch;

		DataGridView^ dataGridViewDepBoard;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;
	};
}
