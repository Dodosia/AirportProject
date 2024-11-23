#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace MaterialSkin;
using namespace MaterialSkin::Controls;
using namespace System::Data::SqlClient;

namespace Airport 
{
	public ref class ArrivalBoardForm : public System::Windows::Forms::Form
	{
	public:
		ArrivalBoardForm();
		~ArrivalBoardForm();
	private:
		void InitializeComponent(void);
		void LoadFlights();

		MaterialSingleLineTextField^ txtFlight;
		MaterialFlatButton^ btnSearch;

		DataGridView^ dataGridViewArBoard;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;
	};
}
