#pragma once

#include "Menu/MenuAgent.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Data::SqlClient;
using namespace MaterialSkin;
using namespace MaterialSkin::Controls;
using namespace System::Drawing::Printing;

namespace Airport
{
	public ref class MakeNewBaggageForm : public System::Windows::Forms::Form
	{
	public:
		MakeNewBaggageForm();
		MakeNewBaggageForm(String^ passId);
		~MakeNewBaggageForm();
		void btnAdd_Click(Object^ sender, EventArgs^ e);
	private:
		void InitializeComponent();
		void PrintPage(Object^ sender, PrintPageEventArgs^ e);
		void btnMakeTag_Click(Object^ sender, EventArgs^ e);
		int GetNextBaggageId();

		Bitmap^ GenerateBarcode(String^ data);

		ComboBox^ cmbDescription;
		MaterialSingleLineTextField^ txtPassId;
		MaterialSingleLineTextField^ txtId;
		MaterialSingleLineTextField^ txtWeight;
		MaterialSingleLineTextField^ txtDescription;
		Label^ lblMaxWeight;

		MaterialFlatButton^ btnAdd;
		MaterialFlatButton^ btnMakeTag;

		PrintDocument^ printDoc;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;

	};
}