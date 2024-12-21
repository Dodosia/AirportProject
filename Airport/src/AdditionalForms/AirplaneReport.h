#pragma once

#include "menu/MenuTech.h"

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
    public ref class AirplaneReportForm : public Form
    {
    public:
        AirplaneReportForm(String^ airplaneId, String^ model, String^ capacity, String^ baggageWeight, String^ year);
        ~AirplaneReportForm();
    private:
        void InitializeComponent();
        void PrintPageHandler(System::Object^ sender, PrintPageEventArgs^ e);
        void saveReportButton_Click(System::Object^ sender, System::EventArgs^ e);

        DataGridView^ dataGridView;
        MaterialRaisedButton^ saveReportButton;
        String^ _airplaneId;
        String^ _model;
        String^ _capacity;
        String^ _baggageWeight;
        String^ _year;
        String^ date;

        MaterialSingleLineTextField^ fullNameTextBox;
    };
}