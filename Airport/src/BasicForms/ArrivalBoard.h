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
using namespace System::Threading::Tasks;
using namespace System::Threading;
using namespace Microsoft::Web::WebView2::WinForms;
using namespace Microsoft::Web::WebView2::Core;

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
		void LoadWebBrowser();
		void dataGridViewDepBoard_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
		void UpdateFlightStatusInDatabase(String^ flightId, String^ newStatus);
		void UpdateTablo(System::Object^ sender, System::EventArgs^ e);
		void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);
		void btnClear_Click(System::Object^ sender, System::EventArgs^ e);
		void dataGridViewDepBoard_CellBeginEdit(Object^ sender, DataGridViewCellCancelEventArgs^ e);
		void UpdateFlightStatusAndTimeInDatabase(String^ flightId, String^ newStatus, String^ newTime);
		void dataGridViewDepBoard_CellFormatting(System::Object^ sender, System::Windows::Forms::DataGridViewCellFormattingEventArgs^ e);

		System::Windows::Forms::Timer^ updateTimer;
		MaterialSingleLineTextField^ txtFlight;
		MaterialFlatButton^ btnSearch;
		MaterialFlatButton^ btnClear;
		WebBrowser^ webBrowser;
		DataGridView^ dataGridViewArBoard;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;
		String^ previousStatus;
	};
}
