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
using namespace System::Diagnostics;
using namespace System::IO;
using namespace ZXing;
using namespace ZXing::Common;
using namespace System::Drawing::Drawing2D;

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

		void btnAdd_Click(Object^ sender, EventArgs^ e);
		Bitmap^ GenerateBarcode(String^ data);

		ComboBox^ cmbDescription;
		MaterialSingleLineTextField^ txtPassId;
		MaterialSingleLineTextField^ txtId;
		MaterialSingleLineTextField^ txtWeight;
		ComboBox^ txtDescription;

		MaterialFlatButton^ btnAdd;
		MaterialFlatButton^ btnMakeTag;

		PrintDocument^ printDoc;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;
		Bitmap^ barcodeBitmap;
	};
}