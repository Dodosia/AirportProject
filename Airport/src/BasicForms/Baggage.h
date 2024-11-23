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
	private:
		void InitializeComponent(void);
		void LoadBaggage();
		void dataGridViewBaggage_CellDoubleClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
		void btnEdit_Click(Object^ sender, EventArgs^ e);

		MaterialSingleLineTextField^ txtId;
		MaterialSingleLineTextField^ txtTalon;
		MaterialSingleLineTextField^ txtTicket;

		MaterialFlatButton^ btnSearch;
		MaterialFlatButton^ btnEdit;
		MaterialFlatButton^ btnDelete;

		Panel^ panelButtons;

		DataGridView^ dataGridViewBaggage;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;
	};
}
