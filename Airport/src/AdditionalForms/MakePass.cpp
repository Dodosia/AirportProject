#include "MakePass.h"

namespace Airport
{
    MakePassForm::MakePassForm(String^ id, String^ ticket, String^ seat)
    {
        InitializeComponent(id, ticket, seat);
    }

    MakePassForm::~MakePassForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void MakePassForm::InitializeComponent(String^ id, String^ ticket, String^ seat)
    {
        this->components = gcnew System::ComponentModel::Container();
        this->StartPosition = FormStartPosition::CenterScreen;

        System::Drawing::Icon^ icon = gcnew System::Drawing::Icon("main_logo.ico");
        this->Icon = icon;
        this->Text = "Посадочный талон";

        printDoc = gcnew PrintDocument();
        printDoc->PrintPage += gcnew PrintPageEventHandler(this, &MakePassForm::PrintPage);

        int leftMargin = 20;
        int topMargin = 20;
        int controlHeight = 40;
        int verticalSpacing = 10;

        this->txtId = gcnew MaterialSingleLineTextField();
        this->txtTicketId = gcnew MaterialSingleLineTextField();
        this->txtSeat = gcnew MaterialSingleLineTextField();

        this->txtId->Hint = "Номер талона";
        this->txtTicketId->Hint = "Номер билета";
        this->txtSeat->Hint = "Номер места";

        this->txtId->Text = id;
        this->txtTicketId->Text = ticket;
        this->txtSeat->Text = seat;

        this->txtId->Location = System::Drawing::Point(leftMargin, topMargin);
        this->txtTicketId->Location = System::Drawing::Point(leftMargin, topMargin + 2 * (controlHeight + verticalSpacing));
        this->txtSeat->Location = System::Drawing::Point(leftMargin, topMargin + 3 * (controlHeight + verticalSpacing));

        this->txtId->Size = System::Drawing::Size(250, controlHeight);
        this->txtTicketId->Size = System::Drawing::Size(250, controlHeight);
        this->txtSeat->Size = System::Drawing::Size(250, controlHeight);

        this->Controls->Add(this->txtId);
        this->Controls->Add(this->txtTicketId);
        this->Controls->Add(this->txtSeat);

        this->btnAdd = gcnew MaterialFlatButton();
        this->btnAdd->Text = "Изменить";
        this->btnAdd->Location = System::Drawing::Point(leftMargin, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnAdd->Size = System::Drawing::Size(120, controlHeight);

        this->btnMakePass = gcnew MaterialFlatButton();
        this->btnMakePass->Text = "Печать";
        this->btnMakePass->Location = System::Drawing::Point(leftMargin + 150, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnMakePass->Size = System::Drawing::Size(120, controlHeight);
        this->btnMakePass->Click += gcnew EventHandler(this, &MakePassForm::btnMakePass_Click);

        this->Controls->Add(this->btnAdd);
        this->Controls->Add(this->btnMakePass);
    }

    void MakePassForm::PrintPage(Object^ sender, PrintPageEventArgs^ e)
    {
        SqlConnection^ connection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");
        connection->Open();
        SqlCommand^ command = gcnew SqlCommand("CreatePass", connection);
        command->CommandType = CommandType::StoredProcedure;

        command->Parameters->Add(gcnew SqlParameter("@ticket", SqlDbType::Int))->Value = Convert::ToInt32(this->txtTicketId->Text);

        command->Parameters->Add(gcnew SqlParameter("@passanger", SqlDbType::VarChar, 50))->Direction = ParameterDirection::Output;
        command->Parameters->Add(gcnew SqlParameter("@flight", SqlDbType::VarChar, 6))->Direction = ParameterDirection::Output;
        command->Parameters->Add(gcnew SqlParameter("@date", SqlDbType::Date))->Direction = ParameterDirection::Output;
        command->Parameters->Add(gcnew SqlParameter("@time", SqlDbType::Time))->Direction = ParameterDirection::Output;
        command->Parameters->Add(gcnew SqlParameter("@citydepart", SqlDbType::VarChar, 15))->Direction = ParameterDirection::Output;
        command->Parameters->Add(gcnew SqlParameter("@cityarriv", SqlDbType::VarChar, 15))->Direction = ParameterDirection::Output;
        command->Parameters->Add(gcnew SqlParameter("@aerdepart", SqlDbType::VarChar, 3))->Direction = ParameterDirection::Output;
        command->Parameters->Add(gcnew SqlParameter("@aerarriv", SqlDbType::VarChar, 3))->Direction = ParameterDirection::Output;

        command->ExecuteNonQuery();

        String^ passenger = command->Parameters["@passanger"]->Value->ToString();
        String^ flight = command->Parameters["@flight"]->Value->ToString();
        String^ flightDate = Convert::ToDateTime(command->Parameters["@date"]->Value).ToShortDateString();
        String^ flightTime = command->Parameters["@time"]->Value->ToString();
        String^ cityDepart = command->Parameters["@citydepart"]->Value->ToString();
        String^ cityArriv = command->Parameters["@cityarriv"]->Value->ToString();
        String^ aerDepart = command->Parameters["@aerdepart"]->Value->ToString();
        String^ aerArriv = command->Parameters["@aerarriv"]->Value->ToString();

        Graphics^ gfx = e->Graphics;
        System::Drawing::Font^ titleFont = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        System::Drawing::Font^ boldFont = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
        System::Drawing::Font^ largeBoldFont = gcnew System::Drawing::Font("Arial", 28, FontStyle::Bold);
        System::Drawing::Font^ regularFont = gcnew System::Drawing::Font("Arial", 12);
        System::Drawing::Font^ smallFont = gcnew System::Drawing::Font("Arial", 10); 
        Brush^ brush = Brushes::Black;
        Pen^ pen = gcnew Pen(Color::Black, 2);

        int width = 800; 
        int height = 300;

        gfx->DrawRectangle(pen, 10, 10, width - 20, height); 
        System::Drawing::Bitmap^ barcodeImage = GenerateBarcode(this->txtTicketId->Text);
        barcodeImage->RotateFlip(RotateFlipType::Rotate90FlipNone); 
        gfx->DrawImage(barcodeImage, 15, 15, 100, height - 10); 

        int dataStartX = 110;

        gfx->DrawString("AEROFLOT", titleFont, brush, 45, 20);

   
        gfx->DrawString(passenger, boldFont, brush, width - 500, 20);  // ФИО справа

        gfx->DrawString(flight, boldFont, brush, dataStartX, 60);
        gfx->DrawString(flightDate, regularFont, brush, dataStartX, 90);

        gfx->DrawString(aerDepart + " - " + aerArriv, largeBoldFont, brush, width - 380, 70);

        //gfx->DrawString("Gate: D25", boldFont, brush, dataStartX, 140);
        gfx->DrawString("Gate closed: " + flightTime, boldFont, brush, dataStartX, 140);
        gfx->DrawString("Seat - Место: " + this->txtSeat->Text, boldFont, brush, dataStartX, 180);

        gfx->DrawString(cityDepart + " - " + cityArriv, regularFont, brush, width - 350, 260);

        gfx->DrawString("Порядковый номер регистрации: " + this->txtId->Text, smallFont, brush, 45, 270);

        Pen^ dashedPen = gcnew Pen(Color::Black, 2);
        dashedPen->DashStyle = System::Drawing::Drawing2D::DashStyle::Dash;
        gfx->DrawLine(dashedPen, 650, 10, 650, height + 10);
    }

    void MakePassForm::btnMakePass_Click(Object^ sender, EventArgs^ e)
    {
        PrintDocument^ printDoc = gcnew PrintDocument();
        String^ pdfPath = Path::Combine(Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments), "AirplaneTag.pdf");

        printDoc->PrinterSettings->PrinterName = "Microsoft Print to PDF";
        printDoc->PrinterSettings->PrintToFile = true;
        printDoc->PrinterSettings->PrintFileName = pdfPath;

        printDoc->PrintPage += gcnew PrintPageEventHandler(this, &MakePassForm::PrintPage);

        printDoc->Print();

        if (File::Exists(pdfPath))
        {
            Process::Start(pdfPath);
        }

        this->Close();
    }

    Bitmap^ MakePassForm::GenerateBarcode(String^ data)
    {
        ZXing::BarcodeWriter^ writer = gcnew ZXing::BarcodeWriter();
        writer->Format = ZXing::BarcodeFormat::PDF_417;

        ZXing::Common::EncodingOptions^ options = gcnew ZXing::Common::EncodingOptions();
        writer->Options = options;

        System::Drawing::Bitmap^ barcodeBitmap = writer->Write(data);
        return barcodeBitmap;
    }
}
