#include "MakeNewPass.h"

namespace Airport
{
    MakeNewPassForm::MakeNewPassForm()
    {
        InitializeComponent();
        this->txtId->Text = GetNextTicketId().ToString();
        this->btnAdd->Text = "Добавить";
        this->btnAdd->Click += gcnew EventHandler(this, &MakeNewPassForm::btnAdd_Click);
    }

    MakeNewPassForm::MakeNewPassForm(String^ ticketId) : _ticketId(ticketId)
    {
        InitializeComponent();
        SqlConnection^ connection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");
        connection->Open();

        SqlCommand^ command = gcnew SqlCommand("SELECT Id FROM ПосадочныйТалон WHERE НомерБилета = @ticketId", connection);
        command->Parameters->Add(gcnew SqlParameter("@ticketId", SqlDbType::Int))->Value = Convert::ToInt32(ticketId);
        Object^ result = command->ExecuteScalar();

        SqlCommand^ command2 = gcnew SqlCommand("SELECT Место FROM ПосадочныйТалон WHERE НомерБилета = @ticketId", connection);
        command2->Parameters->Add(gcnew SqlParameter("@ticketId", SqlDbType::Int))->Value = Convert::ToInt32(ticketId);
        Object^ result2 = command2->ExecuteScalar();

        if (result != nullptr && result != DBNull::Value)
        {
            String^ id = result->ToString();
            String^ seat = result2->ToString();
            this->txtId->Text = id;
            this->txtSeat->Text = seat;
            this->txtTicketId->Text = ticketId;
            this->btnAdd->Text = "Изменить";
        }
        else
        {
            this->txtId->Text = GetNextTicketId().ToString();  // Generate next ID
            this->btnAdd->Text = "Добавить";
            this->txtTicketId->Text = ticketId;
        }
    }

    MakeNewPassForm::~MakeNewPassForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void MakeNewPassForm::InitializeComponent()
    {
        this->components = gcnew System::ComponentModel::Container();

        System::Drawing::Icon^ icon = gcnew System::Drawing::Icon("main_logo.ico");
        this->Icon = icon;
        this->Text = "Посадочный талон";
        this->StartPosition = FormStartPosition::CenterScreen;

        printDoc = gcnew PrintDocument();
        printDoc->PrintPage += gcnew PrintPageEventHandler(this, &MakeNewPassForm::PrintPage);

        int leftMargin = 20;
        int topMargin = 20;
        int controlHeight = 40;
        int verticalSpacing = 10;

        this->txtId = gcnew MaterialSingleLineTextField();
        this->txtTicketId = gcnew MaterialSingleLineTextField();
        this->txtSeat = gcnew MaterialSingleLineTextField();

        this->txtId->Location = System::Drawing::Point(leftMargin + 90, topMargin);
        this->txtTicketId->Location = System::Drawing::Point(leftMargin + 90, txtId->Bottom + 50);
        this->txtSeat->Location = System::Drawing::Point(leftMargin + 90, txtTicketId->Bottom + 50);

        this->txtId->Size = System::Drawing::Size(120, controlHeight);
        this->txtTicketId->Size = System::Drawing::Size(120, controlHeight);
        this->txtSeat->Size = System::Drawing::Size(110, controlHeight);

        this->Controls->Add(this->txtId);
        this->Controls->Add(this->txtTicketId);
        this->Controls->Add(this->txtSeat);

        Label^ labelId = gcnew Label();
        labelId->Text = "Номер талона:";
        labelId->Location = System::Drawing::Point(leftMargin, topMargin + (controlHeight / 2) - 10);
        labelId->Size = System::Drawing::Size(90, 20);
        this->Controls->Add(labelId);

        Label^ labelTicketId = gcnew Label();
        labelTicketId->Text = "Номер билета:";
        labelTicketId->Location = System::Drawing::Point(leftMargin, txtId->Bottom + 30 + (controlHeight / 2) - 10);
        labelTicketId->Size = System::Drawing::Size(90, 20);
        this->Controls->Add(labelTicketId);

        Label^ labelSeat = gcnew Label();
        labelSeat->Text = "Номер места:";
        labelSeat->Location = System::Drawing::Point(leftMargin, txtTicketId->Bottom + 30 + (controlHeight / 2) - 10);
        labelSeat->Size = System::Drawing::Size(90, 20);
        this->Controls->Add(labelSeat);

        this->btnAdd = gcnew MaterialFlatButton();
        this->btnAdd->Text = "Добавить";
        this->btnAdd->Location = System::Drawing::Point(leftMargin, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnAdd->Click += gcnew EventHandler(this, &MakeNewPassForm::btnAdd_Click);
        this->btnAdd->Size = System::Drawing::Size(120, controlHeight);

        this->btnMakePass = gcnew MaterialFlatButton();
        this->btnMakePass->Text = "Печать";
        this->btnMakePass->Location = System::Drawing::Point(leftMargin + 150, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnMakePass->Size = System::Drawing::Size(120, controlHeight);
        this->btnMakePass->Click += gcnew EventHandler(this, &MakeNewPassForm::btnMakePass_Click);

        this->Controls->Add(this->btnAdd);
        this->Controls->Add(this->btnMakePass);

        this->btnSelectSeat = gcnew Button();
        this->btnSelectSeat->Size = System::Drawing::Size(30, 30); 
        this->btnSelectSeat->Location = System::Drawing::Point(this->txtSeat->Right + 10, this->txtSeat->Top);
        this->btnSelectSeat->BackgroundImage = System::Drawing::Image::FromFile("armchair.ico");
        this->btnSelectSeat->BackgroundImageLayout = ImageLayout::Stretch;
        this->btnSelectSeat->FlatStyle = FlatStyle::Flat;
        this->btnSelectSeat->FlatAppearance->BorderSize = 0; 
        this->btnSelectSeat->Click += gcnew EventHandler(this, &MakeNewPassForm::btnOpenSeatSelection_Click);

        this->Controls->Add(this->btnSelectSeat);
    }

    void MakeNewPassForm::PrintPage(Object^ sender, PrintPageEventArgs^ e)
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


        gfx->DrawString(passenger, boldFont, brush, width - 500, 20);

        gfx->DrawString(flight, boldFont, brush, dataStartX, 60);
        gfx->DrawString(flightDate, regularFont, brush, dataStartX, 90);

        gfx->DrawString(aerDepart + " - " + aerArriv, largeBoldFont, brush, width - 380, 70);

        gfx->DrawString("Gate closed: " + flightTime, boldFont, brush, dataStartX, 140);
        gfx->DrawString("Seat - Место: " + this->txtSeat->Text, boldFont, brush, dataStartX, 180);

        gfx->DrawString(cityDepart + " - " + cityArriv, regularFont, brush, width - 350, 260);

        gfx->DrawString("Порядковый номер регистрации: " + this->txtId->Text, smallFont, brush, 45, 270);

        Pen^ dashedPen = gcnew Pen(Color::Black, 2);
        dashedPen->DashStyle = System::Drawing::Drawing2D::DashStyle::Dash;
        gfx->DrawLine(dashedPen, 650, 10, 650, height + 10);
    }

    void MakeNewPassForm::btnMakePass_Click(Object^ sender, EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(this->txtId->Text) ||
            String::IsNullOrWhiteSpace(this->txtSeat->Text) ||
            String::IsNullOrWhiteSpace(this->txtTicketId->Text))
        {
            MessageBox::Show("Все поля должны быть заполнены.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        PrintDocument^ printDoc = gcnew PrintDocument();
        String^ pdfPath = Path::Combine(Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments), "AirplaneTag.pdf");

        printDoc->PrinterSettings->PrinterName = "Microsoft Print to PDF";
        printDoc->PrinterSettings->PrintToFile = true;
        printDoc->PrinterSettings->PrintFileName = pdfPath;

        printDoc->PrintPage += gcnew PrintPageEventHandler(this, &MakeNewPassForm::PrintPage);

        printDoc->Print();

        if (File::Exists(pdfPath))
        {
            Process::Start(pdfPath);
        }

        this->Close();
    }

    void MakeNewPassForm::CheckTicketExists(String^ ticketId)
    {
        SqlConnection^ connection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");
        connection->Open();
        SqlCommand^ command = gcnew SqlCommand("SELECT COUNT(*) FROM ПосадочныйТалон WHERE ПосадочныйТалон.НомерБилета = @ticketId", connection);
        command->Parameters->Add(gcnew SqlParameter("@ticketId", SqlDbType::Int))->Value = Convert::ToInt32(ticketId);

        int count = Convert::ToInt32(command->ExecuteScalar());

        if (count > 0)
        {
            this->btnAdd->Text = "Изменить";
        }
        else
        {
            this->btnAdd->Text = "Добавить";
        }
    }

    void MakeNewPassForm::btnAdd_Click(Object^ sender, EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(this->txtId->Text) ||
            String::IsNullOrWhiteSpace(this->txtSeat->Text) ||
            String::IsNullOrWhiteSpace(this->txtTicketId->Text))
        {
            MessageBox::Show("Все поля должны быть заполнены.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        if (this->btnAdd->Text == "Добавить")
        {
            AddNewTicket();
        }
        else if (this->btnAdd->Text == "Изменить")
        {
            UpdateTicket();
        }
    }

    void MakeNewPassForm::AddNewTicket()
    {
        int id;
        if (!Int32::TryParse(this->txtId->Text, id))
        {
            //MessageBox::Show("Неверный формат для ID.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        int ticketId;
        if (!Int32::TryParse(this->txtTicketId->Text, ticketId))
        {
            //MessageBox::Show("Неверный формат для номера билета.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return; 
        }

        String^ seat = this->txtSeat->Text;

        SqlConnection^ connection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");
        
        connection->Open();

        SqlCommand^ command = gcnew SqlCommand("AddNewBoardingPass", connection);
        command->CommandType = CommandType::StoredProcedure;

        command->Parameters->Add(gcnew SqlParameter("@Id", SqlDbType::Int))->Value = id;
        command->Parameters->Add(gcnew SqlParameter("@НомерБилета", SqlDbType::Int))->Value = ticketId;
        command->Parameters->Add(gcnew SqlParameter("@Место", SqlDbType::NVarChar, 10))->Value = seat;

        SqlParameter^ messageParam = gcnew SqlParameter("@message", SqlDbType::VarChar, 100);
        messageParam->Direction = ParameterDirection::Output;
        command->Parameters->Add(messageParam);

        try
        {
            command->ExecuteNonQuery();
        }
        catch (SqlException^ ex)
        {
            MessageBox::Show("Ошибка добавления билета: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }

        connection->Close();

        String^ message = messageParam->Value->ToString();

        MessageBox::Show(message);

        for each (Form ^ frm in Application::OpenForms)
        {
            if (frm->Name == "MenuAgentForm")
            {
                MenuAgentForm^ menuForm = dynamic_cast<MenuAgentForm^>(frm);
                if (menuForm != nullptr)
                {
                    for each (Control ^ control in menuForm->boardingPassTab->Controls)
                    {
                        BoardingPassForm^ boardingPassForm = dynamic_cast<BoardingPassForm^>(control);
                        if (boardingPassForm != nullptr)
                        {
                            boardingPassForm->LoadBoardingPass(); // Перезагрузка данных
                        }
                    }
                }
            }
        }

        this->Close();
    }

    void MakeNewPassForm::UpdateTicket()
    {

        SqlConnection^ connection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");
        connection->Open();

        SqlCommand^ command = gcnew SqlCommand("UpdateBoardingPass", connection);
        command->CommandType = CommandType::StoredProcedure;

        command->Parameters->Add(gcnew SqlParameter("@Id", SqlDbType::Int))->Value = Convert::ToInt32(this->txtId->Text);
        command->Parameters->Add(gcnew SqlParameter("@НомерБилета", SqlDbType::Int))->Value = Convert::ToInt32(this->txtTicketId->Text);
        command->Parameters->Add(gcnew SqlParameter("@Место", SqlDbType::NVarChar, 10))->Value = this->txtSeat->Text;

        SqlParameter^ messageParam = gcnew SqlParameter("@message", SqlDbType::NVarChar, 100);
        messageParam->Direction = ParameterDirection::Output;
        command->Parameters->Add(messageParam);

        try
        {
            command->ExecuteNonQuery();
        }
        catch (SqlException^ ex)
        {
            MessageBox::Show("Ошибка обновления билета: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }

        String^ message = messageParam->Value->ToString();
        MessageBox::Show(message, "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
        connection->Close();

        for each (Form ^ frm in Application::OpenForms)
        {
            if (frm->Name == "MenuAgentForm")
            {
                MenuAgentForm^ menuForm = dynamic_cast<MenuAgentForm^>(frm);
                if (menuForm != nullptr)
                {
                    for each (Control ^ control in menuForm->boardingPassTab->Controls)
                    {
                        BoardingPassForm^ boardingPassForm = dynamic_cast<BoardingPassForm^>(control);
                        if (boardingPassForm != nullptr)
                        {
                            boardingPassForm->LoadBoardingPass(); // Перезагрузка данных
                        }
                    }
                }
            }
        }

        this->Close();
    }

    int MakeNewPassForm::GetNextTicketId()
    {
        SqlConnection^ connection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");
        connection->Open();

        String^ query = "SELECT MAX(Id) FROM ПосадочныйТалон";
        SqlCommand^ command = gcnew SqlCommand(query, connection);

        Object^ result = command->ExecuteScalar();

        if (result == DBNull::Value || result == nullptr)
        {
            return 1;
        }
        else
        {
            return Convert::ToInt32(result) + 1; 
        }
    }

    Bitmap^ MakeNewPassForm::GenerateBarcode(String^ data)
    {
        ZXing::BarcodeWriter^ writer = gcnew ZXing::BarcodeWriter();
        writer->Format = ZXing::BarcodeFormat::PDF_417;

        ZXing::Common::EncodingOptions^ options = gcnew ZXing::Common::EncodingOptions();
        writer->Options = options;

        System::Drawing::Bitmap^ barcodeBitmap = writer->Write(data);
        return barcodeBitmap;
    }

    void MakeNewPassForm::SetSelectedSeat(String^ seat)
    {
        this->txtSeat->Text = seat;
    }

    void MakeNewPassForm::btnOpenSeatSelection_Click(System::Object^ sender, System::EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(this->txtTicketId->Text))
        {
            MessageBox::Show("Необходимо заполнить номер билета", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        Form^ seatForm = gcnew SeatSelectionForm(this);
        seatForm->ShowDialog();
    }
}
