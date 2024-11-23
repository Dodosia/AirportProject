#include "MakePass.h"

namespace Airport
{
    MakePassForm::MakePassForm(String^ id, String^ pasId, String^ ticket, String^ seat)
    {
        InitializeComponent(id, pasId, ticket, seat);
    }

    MakePassForm::~MakePassForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void MakePassForm::InitializeComponent(String^ id, String^ pasId, String^ ticket, String^ seat)
    {
        this->components = gcnew System::ComponentModel::Container();
        this->StartPosition = FormStartPosition::CenterScreen;

        System::Drawing::Icon^ icon = gcnew System::Drawing::Icon("main_logo.ico");
        this->Icon = icon;
        this->Text = "���������� �����";

        printDoc = gcnew PrintDocument();
        printDoc->PrintPage += gcnew PrintPageEventHandler(this, &MakePassForm::PrintPage);

        int leftMargin = 20;
        int topMargin = 20;
        int controlHeight = 40;
        int verticalSpacing = 10; 

        this->txtId = gcnew MaterialSingleLineTextField();
        this->txtTicketId = gcnew MaterialSingleLineTextField();
        this->txtSeat = gcnew MaterialSingleLineTextField();
        this->txtPassangerId = gcnew MaterialSingleLineTextField();

        this->txtId->Hint = "����� ������";
        this->txtTicketId->Hint = "����� ������";
        this->txtSeat->Hint = "����� �����";
        this->txtPassangerId->Hint = "Id ���������";

        this->txtId->Text = id;
        this->txtTicketId->Text = ticket;
        this->txtPassangerId->Text = pasId;
        this->txtSeat->Text = seat;

        this->txtId->Location = System::Drawing::Point(leftMargin, topMargin);
        this->txtPassangerId->Location = System::Drawing::Point(leftMargin, topMargin + controlHeight + verticalSpacing);
        this->txtTicketId->Location = System::Drawing::Point(leftMargin, topMargin + 2 * (controlHeight + verticalSpacing));
        this->txtSeat->Location = System::Drawing::Point(leftMargin, topMargin + 3 * (controlHeight + verticalSpacing));

        this->txtId->Size = System::Drawing::Size(250, controlHeight);
        this->txtPassangerId->Size = System::Drawing::Size(250, controlHeight);
        this->txtTicketId->Size = System::Drawing::Size(250, controlHeight);
        this->txtSeat->Size = System::Drawing::Size(250, controlHeight);

        this->Controls->Add(this->txtId);
        this->Controls->Add(this->txtPassangerId);
        this->Controls->Add(this->txtTicketId);
        this->Controls->Add(this->txtSeat);

        this->btnAdd = gcnew MaterialFlatButton();
        this->btnAdd->Text = "��������";
        this->btnAdd->Location = System::Drawing::Point(leftMargin, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnAdd->Size = System::Drawing::Size(120, controlHeight);

        this->btnMakePass = gcnew MaterialFlatButton();
        this->btnMakePass->Text = "������";
        this->btnMakePass->Location = System::Drawing::Point(leftMargin + 150, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnMakePass->Size = System::Drawing::Size(120, controlHeight);
        this->btnMakePass->Click += gcnew EventHandler(this, &MakePassForm::btnMakePass_Click);

        this->Controls->Add(this->btnAdd);
        this->Controls->Add(this->btnMakePass);
    }

    void MakePassForm::PrintPage(Object^ sender, PrintPageEventArgs^ e)
    {
        Graphics^ g = e->Graphics;

        System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 14);
        Brush^ brush = Brushes::Black;

        String^ text = "���������� �����\n\n";
        text += "����� ������: " + this->txtId->Text + "\n";
        text += "����� ������: " + this->txtTicketId->Text + "\n";
        text += "����� �����: " + this->txtSeat->Text + "\n";
        text += "Id ���������: " + this->txtPassangerId->Text;

        g->DrawString(text, font, brush, 20, 20);

        Bitmap^ bitmap = gcnew Bitmap(600, 400);
        Graphics^ imageGraphics = Graphics::FromImage(bitmap);

        imageGraphics->DrawString(text, font, brush, 20, 20);

        String^ filePath = "pass.png";
        bitmap->Save(filePath, System::Drawing::Imaging::ImageFormat::Png);

        delete bitmap;
        delete imageGraphics;

        System::Diagnostics::Process::Start(filePath);

        e->HasMorePages = false;
    }

    void MakePassForm::btnMakePass_Click(Object^ sender, EventArgs^ e)
    {
        printDoc->Print();
    }
}
