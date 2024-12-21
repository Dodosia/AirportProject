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
	public ref class FlightsForm : public System::Windows::Forms::Form
	{
	public:
		FlightsForm(void);
		~FlightsForm();
	private:
		void InitializeComponent(void);
		void LoadFlights();

		void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);
		void btnClear_Click(System::Object^ sender, System::EventArgs^ e);

		DataGridView^ dataGridViewFlights;
		ListView^ listViewFlights;
		SqlConnection^ sqlConnection;
		MaterialSingleLineTextField^ txtNumber;
		MaterialSingleLineTextField^ txtAirport;
		MaterialFlatButton^ btnSearch;
		MaterialFlatButton^ btnClear;

		IContainer^ components;
	};
}
