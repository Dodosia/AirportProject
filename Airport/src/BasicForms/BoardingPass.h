#pragma once

#include "AdditionalForms/MakePass.h"
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
	public ref class BoardingPassForm : public System::Windows::Forms::Form
	{
	public:
		BoardingPassForm();
		~BoardingPassForm();
		void LoadBoardingPass();
	private:
		void InitializeComponent(void);
		void dataGridViewBoardingPass_CellDoubleClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
		void btnEdit_Click(Object^ sender, EventArgs^ e);
		void btnDelete_Click(System::Object^ sender, System::EventArgs^ e);
		void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);
		void btnClear_Click(System::Object^ sender, System::EventArgs^ e);

		MaterialSingleLineTextField^ txtId;
		MaterialSingleLineTextField^ txtPasId;
		MaterialSingleLineTextField^ txtTicket;

		MaterialFlatButton^ btnSearch;
		MaterialFlatButton^ btnClear;
		MaterialRaisedButton^ btnEdit;
		MaterialRaisedButton^ btnDelete;

		Panel^ panelButtons;
		DataGridView^ dataGridViewBoardingPass;

		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;
	};

}
