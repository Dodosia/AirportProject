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
	public ref class TechFlight : public System::Windows::Forms::Form
	{
	public:
		TechFlight();
		~TechFlight();
	private:
		void InitializeComponent();
		void LoadFlights();

		void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);
		void btnClear_Click(System::Object^ sender, System::EventArgs^ e);
		void dataGridViewFlights_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
		void dataGridViewFlights_CellBeginEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellCancelEventArgs^ e);

		String^ GetAirplaneStatusById(String^ airplaneId);
		System::Data::DataTable^ TechFlight::GetAvailableAirplanes();

		String^ originalAirplaneId;

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
