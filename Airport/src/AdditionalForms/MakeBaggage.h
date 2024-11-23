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
using namespace System::Drawing::Printing;

namespace Airport
{
	public ref class MakeBaggageForm : public System::Windows::Forms::Form
	{
	public:
		MakeBaggageForm(String^ id, String^ talon, String^ weight, String^ dicr);
		~MakeBaggageForm();
	private:
		void InitializeComponent(String^ id, String^ talon, String^ weight, String^ dicr);
		void PrintPage(Object^ sender, PrintPageEventArgs^ e);
		void btnMakeTag_Click(Object^ sender, EventArgs^ e);

		MaterialSingleLineTextField^ txtPassId;
		MaterialSingleLineTextField^ txtId;
		MaterialSingleLineTextField^ txtWeight;
		MaterialSingleLineTextField^ txtDescription;

		MaterialFlatButton^ btnAdd;
		MaterialFlatButton^ btnMakeTag;

		PrintDocument^ printDoc;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;

	};
}