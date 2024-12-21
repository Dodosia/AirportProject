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
	public ref class AirportsForm : public System::Windows::Forms::Form
	{
	public:
		AirportsForm();
		~AirportsForm();
	private:
		void InitializeComponent(void);
		void loadAirports();
		void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);
		void btnClear_Click(System::Object^ sender, System::EventArgs^ e);

		DataGridView^ dataGridViewAeroports;
		SqlConnection^ sqlConnection;
		IContainer^ components;
		MaterialSingleLineTextField^ txtNumber;
		MaterialSingleLineTextField^ txtAirport;
		MaterialSingleLineTextField^ txtTown;
		MaterialFlatButton^ btnSearch;
		MaterialFlatButton^ btnClear;
	};


}
