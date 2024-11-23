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
	public ref class TicketsForm : public System::Windows::Forms::Form
	{
	public:
		TicketsForm();
		~TicketsForm();
	private:
		void InitializeComponent(void);
		void LoadTickets();

		MaterialSingleLineTextField^ txtId;
		MaterialSingleLineTextField^ txtPasId;
		MaterialSingleLineTextField^ txtFlight;
		MaterialSingleLineTextField^ txtDate;

		MaterialFlatButton^ btnSearch;

		DataGridView^ dataGridViewTickets;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;
	};
}