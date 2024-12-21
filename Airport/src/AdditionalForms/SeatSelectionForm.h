#pragma once

#include "MakeNewPass.h"

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
using namespace System::Collections::Generic;

namespace Airport
{
    ref class MakeNewPassForm;

    public ref class SeatSelectionForm : public Form
    {
    public:
        SeatSelectionForm(MakeNewPassForm^ parent);

    private:
        MakeNewPassForm^ parentForm;
        Panel^ seatPanel;
        void InitializeComponent();
        void CreateSeatButtons();

        void btnSeat_Click(System::Object^ sender, System::EventArgs^ e);
    };
}