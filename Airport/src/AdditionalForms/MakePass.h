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
using namespace System::Diagnostics;
using namespace System::IO;

namespace Airport
{
	public ref class MakePassForm : public System::Windows::Forms::Form
	{
	public:
		MakePassForm(String^ id, String^ ticket, String^ seat);
		~MakePassForm();
	private:
		void InitializeComponent(String^ id, String^ ticket, String^ seat);
		void PrintPage(Object^ sender, PrintPageEventArgs^ e);
		void btnMakePass_Click(Object^ sender, EventArgs^ e);

		Bitmap^ GenerateBarcode(String^ data);

		MaterialSingleLineTextField^ txtPassangerId;
		MaterialSingleLineTextField^ txtId;
		MaterialSingleLineTextField^ txtTicketId;
		MaterialSingleLineTextField^ txtSeat;
	
		MaterialFlatButton^ btnAdd;
		MaterialFlatButton^ btnMakePass;

		PrintDocument^ printDoc;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;
	};

}