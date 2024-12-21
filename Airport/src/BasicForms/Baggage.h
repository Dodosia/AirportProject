#pragma once

#include "AdditionalForms/MakeBaggage.h"
#include "AdditionalForms/MakeNewBaggage.h"

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
	public ref class BaggageForm : public System::Windows::Forms::Form
	{
	public:
		BaggageForm(void);
		~BaggageForm();
		void LoadBaggage();
	private:
		void InitializeComponent(void);
		void dataGridViewBaggage_CellDoubleClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
		void btnEdit_Click(Object^ sender, EventArgs^ e);
		void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);
		void btnClear_Click(System::Object^ sender, System::EventArgs^ e);
		void btnDelete_Click(System::Object^ sender, System::EventArgs^ e);

		MaterialSingleLineTextField^ txtId;
		MaterialSingleLineTextField^ txtTalon;
		MaterialSingleLineTextField^ txtTicket;

		MaterialFlatButton^ btnSearch;
		MaterialFlatButton^ btnClear;
		MaterialRaisedButton^ btnEdit;
		MaterialRaisedButton^ btnDelete;

		Panel^ panelButtons;

		DataGridView^ dataGridViewBaggage;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;
	};
}
