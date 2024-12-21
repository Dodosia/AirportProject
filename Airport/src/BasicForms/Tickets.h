#pragma once

#include "AdditionalForms/MakeNewPass.h"
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
	public ref class TicketsForm : public System::Windows::Forms::Form
	{
	public:
		TicketsForm();
		~TicketsForm();
	private:
		void InitializeComponent(void);
		void LoadTickets();
		void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);
		void btnClear_Click(System::Object^ sender, System::EventArgs^ e);
		void dataGridViewTickets_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);

		MaterialSingleLineTextField^ txtId;
		MaterialSingleLineTextField^ txtPasId;
		MaterialSingleLineTextField^ txtFlight;
		MaterialSingleLineTextField^ txtDate;

		MaterialFlatButton^ btnSearch;
		MaterialFlatButton^ btnClear;

		DataGridView^ dataGridViewTickets;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;
	};
}