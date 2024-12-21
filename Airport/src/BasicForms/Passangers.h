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
	public ref class PassangersForm: public System::Windows::Forms::Form
	{
	public:
		PassangersForm(void);
		~PassangersForm();
	private:
		void InitializeComponent(void);
		void LoadPassangers();
		void btnSearch_Click(System::Object^ sender, System::EventArgs^ e);
		void btnClear_Click(System::Object^ sender, System::EventArgs^ e);
		void dataGridViewPassengers_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e);
		bool CheckIfPassExists(int passengerId);

		DataGridView^ dataGridViewPassangers;
		SqlConnection^ sqlConnection;
		MaterialSingleLineTextField^ txtFio;
		MaterialSingleLineTextField^ txtPassport;
		MaterialSingleLineTextField^ txtPhone;
		MaterialFlatButton^ btnSearch;
		MaterialFlatButton^ btnClear;
		System::ComponentModel::IContainer^ components;
	};
	
}
