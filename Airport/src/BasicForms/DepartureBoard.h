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
		void LoadWebBrowser();
		void dataGridViewDepBoard_CellFormatting(System::Object^ sender, System::Windows::Forms::DataGridViewCellFormattingEventArgs^ e);
		void dataGridViewDepBoard_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
		void UpdateFlightStatusInDatabase(String^ flightId, String^ newStatus);
		void UpdateFlightStatusAndTimeInDatabase(String^ flightId, String^ newStatus, String^ newTime);
		void UpdateTablo(System::Object^ sender, System::EventArgs^ e);
		void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);
		void btnClear_Click(System::Object^ sender, System::EventArgs^ e);
		void dataGridViewDepBoard_CellBeginEdit(Object^ sender, DataGridViewCellCancelEventArgs^ e);
		void UpdateFlightTimeInDatabase(String^ flightId, DateTime^ newTime);
		void HighlightRowAsDelayed(int rowIndex);

		System::Windows::Forms::Timer^ updateTimer;
		MaterialSingleLineTextField^ txtFlight;
		MaterialFlatButton^ btnSearch;
		MaterialFlatButton^ btnClear;
		WebBrowser^ webBrowser;
		DataGridView^ dataGridViewDepBoard;
		SqlConnection^ sqlConnection;
		String^ previousStatus;

		DateTimePicker^ dtpNewDepartureTime;
		System::ComponentModel::IContainer^ components;
	};
}
