#include "MakeNewBaggage.h"

namespace Airport
{
	MakeNewBaggageForm::MakeNewBaggageForm()
	{
		InitializeComponent();
	}

	MakeNewBaggageForm::~MakeNewBaggageForm()
	{
		if (components)
		{
			delete components;
		}
	}

	void MakeNewBaggageForm::InitializeComponent()
	{
        this->components = gcnew System::ComponentModel::Container();
        System::Drawing::Icon^ icon = gcnew System::Drawing::Icon("main_logo.ico");
        this->Icon = icon;
        this->Text = "Багажная бирка";
        this->StartPosition = FormStartPosition::CenterScreen;

        printDoc = gcnew PrintDocument();
        printDoc->PrintPage += gcnew PrintPageEventHandler(this, &MakeNewBaggageForm::PrintPage);

        int leftMargin = 20;
        int topMargin = 20;
        int controlHeight = 40;
        int verticalSpacing = 10;

        this->txtId = gcnew MaterialSingleLineTextField();
        this->txtPassId = gcnew MaterialSingleLineTextField();
        this->txtWeight = gcnew MaterialSingleLineTextField();
        this->txtDescription = gcnew MaterialSingleLineTextField();

        this->txtId->Hint = "Номер бирки";
        this->txtPassId->Hint = "Номер талона";
        this->txtWeight->Hint = "Вес";
        this->txtDescription->Hint = "Описание";

        this->txtId->Location = System::Drawing::Point(leftMargin, topMargin);
        this->txtPassId->Location = System::Drawing::Point(leftMargin, topMargin + controlHeight + verticalSpacing);
        this->txtWeight->Location = System::Drawing::Point(leftMargin, topMargin + 2 * (controlHeight + verticalSpacing));
        this->txtDescription->Location = System::Drawing::Point(leftMargin, topMargin + 3 * (controlHeight + verticalSpacing));

        this->txtId->Size = System::Drawing::Size(250, controlHeight);
        this->txtPassId->Size = System::Drawing::Size(250, controlHeight);
        this->txtWeight->Size = System::Drawing::Size(250, controlHeight);
        this->txtDescription->Size = System::Drawing::Size(250, controlHeight);

        this->Controls->Add(this->txtId);
        this->Controls->Add(this->txtPassId);
        this->Controls->Add(this->txtWeight);
        this->Controls->Add(this->txtDescription);

        this->btnAdd = gcnew MaterialFlatButton();
        this->btnAdd->Text = "Добавить";
        this->btnAdd->Location = System::Drawing::Point(leftMargin, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnAdd->Size = System::Drawing::Size(120, controlHeight);

        this->btnMakeTag = gcnew MaterialFlatButton();
        this->btnMakeTag->Text = "Печать";
        this->btnMakeTag->Location = System::Drawing::Point(leftMargin + 150, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnMakeTag->Size = System::Drawing::Size(120, controlHeight);
        this->btnMakeTag->Click += gcnew EventHandler(this, &MakeNewBaggageForm::btnMakeTag_Click);

        this->Controls->Add(this->btnAdd);
        this->Controls->Add(this->btnMakeTag);
	}

	void MakeNewBaggageForm::PrintPage(Object^ sender, PrintPageEventArgs^ e)
	{
        Graphics^ g = e->Graphics;

        System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 14);
        Brush^ brush = Brushes::Black;

        String^ text = "Багажная бирка\n\n";
        text += "Номер бирки: " + this->txtId->Text + "\n";
        text += "Номер билета: " + this->txtPassId->Text + "\n";
        text += "Вес: " + this->txtWeight->Text + "\n";
        text += "Описание: " + this->txtDescription->Text;

        g->DrawString(text, font, brush, 20, 20);

        Bitmap^ bitmap = gcnew Bitmap(600, 400);
        Graphics^ imageGraphics = Graphics::FromImage(bitmap);

        imageGraphics->DrawString(text, font, brush, 20, 20);

        String^ filePath = "baggageTag.png";
        bitmap->Save(filePath, System::Drawing::Imaging::ImageFormat::Png);

        delete bitmap;
        delete imageGraphics;

        System::Diagnostics::Process::Start(filePath);

        e->HasMorePages = false;
	}

	void MakeNewBaggageForm::btnMakeTag_Click(Object^ sender, EventArgs^ e)
	{
        printDoc->Print();
	}
}
