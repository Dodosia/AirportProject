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
	public ref class PassangersForm: public System::Windows::Forms::Form
	{
	public:
		PassangersForm(void);
		~PassangersForm();
	private:
		void InitializeComponent(void);
		void LoadPassangers();

		DataGridView^ dataGridViewPassangers;
		SqlConnection^ sqlConnection;
		MaterialSingleLineTextField^ txtFio;
		MaterialSingleLineTextField^ txtPassport;
		MaterialSingleLineTextField^ txtPhone;
		MaterialFlatButton^ btnSearch;
		System::ComponentModel::IContainer^ components;
	};
	
}
