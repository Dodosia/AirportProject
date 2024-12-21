#pragma once

#include "SeatSelectionForm.h"
#include "BasicForms/BoardingPass.h"
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

namespace Airport
{
	public ref class MakeNewPassForm : public Form
	{
	public:
		MakeNewPassForm();
		MakeNewPassForm(String^ ticketId);
		~MakeNewPassForm();

		void SetSelectedSeat(String^ seat);
		MaterialSingleLineTextField^ txtTicketId;
	private:
		void InitializeComponent();
		void PrintPage(Object^ sender, PrintPageEventArgs^ e);
		void btnMakePass_Click(Object^ sender, EventArgs^ e);
		void CheckTicketExists(String^ ticketId);
		void btnAdd_Click(Object^ sender, EventArgs^ e);
		void AddNewTicket();
		void UpdateTicket();
		int GetNextTicketId();
		Bitmap^ GenerateBarcode(String^ data);

		void btnOpenSeatSelection_Click(System::Object^ sender, System::EventArgs^ e);
		MaterialSingleLineTextField^ txtId;

		MaterialSingleLineTextField^ txtSeat;
		MaterialFlatButton^ btnAdd;
		MaterialFlatButton^ btnMakePass;
		Button^ btnSelectSeat;
		String^ _ticketId;
		
		PrintDocument^ printDoc;
		SqlConnection^ sqlConnection;
		System::ComponentModel::IContainer^ components;
	};

}