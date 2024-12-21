#include "MakeNewBaggage.h"

namespace Airport
{
	MakeNewBaggageForm::MakeNewBaggageForm()
	{
		InitializeComponent();
        this->txtId->Text = GetNextBaggageId().ToString();
	}

    MakeNewBaggageForm::MakeNewBaggageForm(String^ passId)
    {
        InitializeComponent();
        this->txtId->Text = GetNextBaggageId().ToString();
        this->txtPassId->Text = passId;
    }

	MakeNewBaggageForm::~MakeNewBaggageForm()
	{
		if (components)
		{
			delete components;
		}
	}

    void MakeNewBaggageForm::btnAdd_Click(Object^ sender, EventArgs^ e)
    {
        if (String::IsNullOrWhiteSpace(this->txtId->Text) ||
            String::IsNullOrWhiteSpace(this->txtPassId->Text) ||
            String::IsNullOrWhiteSpace(this->txtWeight->Text) ||
            this->cmbDescription->SelectedItem == nullptr)
        {
            MessageBox::Show("Все поля должны быть заполнены.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        int baggageId = Convert::ToInt32(this->txtId->Text);
        int talonId = Convert::ToInt32(this->txtPassId->Text);
        int weight = Convert::ToInt32(this->txtWeight->Text);
        String^ description = this->cmbDescription->SelectedItem->ToString();

        SqlConnection^ connection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");

        try
        {
            connection->Open();

            SqlCommand^ command = gcnew SqlCommand("AddNewBaggageTag", connection);
            command->CommandType = CommandType::StoredProcedure;

            command->Parameters->Add(gcnew SqlParameter("@Id", SqlDbType::Int))->Value = baggageId;
            command->Parameters->Add(gcnew SqlParameter("@IdТалона", SqlDbType::Int))->Value = talonId;
            command->Parameters->Add(gcnew SqlParameter("@Описание", SqlDbType::VarChar, 20))->Value = description;
            command->Parameters->Add(gcnew SqlParameter("@Вес", SqlDbType::Int))->Value = weight;

            SqlParameter^ messageParam = gcnew SqlParameter("@message", SqlDbType::VarChar, 100);
            messageParam->Direction = ParameterDirection::Output;
            command->Parameters->Add(messageParam);

            command->ExecuteNonQuery();

            String^ message = messageParam->Value->ToString();

            MessageBox::Show(message, "Результат добавления", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        catch (SqlException^ ex)
        {
            MessageBox::Show("Ошибка добавления бирки: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        catch (Exception^ ex)
        {
            MessageBox::Show("Ошибка: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        finally
        {
            connection->Close();
        }

        for each(Form ^ frm in Application::OpenForms)
        {
            if (frm->Name == "MenuAgentForm")
            {
                MenuAgentForm^ menuForm = dynamic_cast<MenuAgentForm^>(frm);
                if (menuForm != nullptr)
                {
                    for each (Control ^ control in menuForm->baggageTab->Controls)
                    {
                        BaggageForm^ boardingPassForm = dynamic_cast<BaggageForm^>(control);
                        if (boardingPassForm != nullptr)
                        {
                            boardingPassForm->LoadBaggage();
                        }
                    }
                }
            }
        }

        this->Close();
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

        this->txtId->Location = System::Drawing::Point(leftMargin + 90, topMargin);
        this->txtPassId->Location = System::Drawing::Point(leftMargin + 90, topMargin + controlHeight + verticalSpacing);
        this->txtWeight->Location = System::Drawing::Point(leftMargin + 90, topMargin + 2 * (controlHeight + verticalSpacing));
    
        this->txtId->Size = System::Drawing::Size(120, controlHeight);
        this->txtPassId->Size = System::Drawing::Size(120, controlHeight);
        this->txtWeight->Size = System::Drawing::Size(120, controlHeight);

        this->Controls->Add(this->txtId);
        this->Controls->Add(this->txtPassId);
        this->Controls->Add(this->txtWeight);

        Label^ labelId = gcnew Label();
        labelId->Text = "Номер бирки:";
        labelId->Location = System::Drawing::Point(leftMargin, topMargin + (controlHeight / 2) - 10);
        labelId->Size = System::Drawing::Size(90, 20);
        this->Controls->Add(labelId);

        Label^ labelTicketId = gcnew Label();
        labelTicketId->Text = "Номер талона:";
        labelTicketId->Location = System::Drawing::Point(leftMargin, txtId->Bottom + 30 + (controlHeight / 2) - 10);
        labelTicketId->Size = System::Drawing::Size(90, 20);
        this->Controls->Add(labelTicketId);

        Label^ labelSeat = gcnew Label();
        labelSeat->Text = "Вес:";
        labelSeat->Location = System::Drawing::Point(leftMargin, txtPassId->Bottom + 30 + (controlHeight / 2) - 10);
        labelSeat->Size = System::Drawing::Size(90, 20);
        this->Controls->Add(labelSeat);

        this->btnAdd = gcnew MaterialFlatButton();
        this->btnAdd->Text = "Добавить";
        this->btnAdd->Location = System::Drawing::Point(leftMargin, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnAdd->Size = System::Drawing::Size(120, controlHeight);
        this->btnAdd->Click += gcnew EventHandler(this, &MakeNewBaggageForm::btnAdd_Click);

        this->btnMakeTag = gcnew MaterialFlatButton();
        this->btnMakeTag->Text = "Печать";
        this->btnMakeTag->Location = System::Drawing::Point(leftMargin + 150, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnMakeTag->Size = System::Drawing::Size(120, controlHeight);
        this->btnMakeTag->Click += gcnew EventHandler(this, &MakeNewBaggageForm::btnMakeTag_Click);

        this->Controls->Add(this->btnAdd);
        this->Controls->Add(this->btnMakeTag);

        this->cmbDescription = gcnew ComboBox();
        this->cmbDescription->DropDownStyle = ComboBoxStyle::DropDownList;
        this->cmbDescription->Items->Add("Спортивный инвентарь");
        this->cmbDescription->Items->Add("Дипломатический");
        this->cmbDescription->Items->Add("Стандартный багаж");
        this->cmbDescription->Items->Add("Ручная кладь");
        this->cmbDescription->SelectedItem = "Стандартный багаж";
        this->cmbDescription->Location = System::Drawing::Point(leftMargin, topMargin + 3 * (controlHeight + verticalSpacing));
        this->cmbDescription->Size = System::Drawing::Size(250, controlHeight);
        this->Controls->Add(this->cmbDescription);
	}

	void MakeNewBaggageForm::PrintPage(Object^ sender, PrintPageEventArgs^ e)
	{
        Graphics^ gfx = e->Graphics;
        System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 14);
        System::Drawing::Font^ font2 = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
        Brush^ brush = Brushes::Black;
        Pen^ pen = gcnew Pen(Color::Black, 2);
        System::Drawing::Font^ titleFont = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);

        int y = 20;

        gfx->DrawString(this->txtId->Text, font, brush, 20, y);
        y += 30;
        gfx->DrawString(this->txtPassId->Text, font, brush, 20, y);
        y += 30;
        gfx->DrawString(this->txtWeight->Text, font, brush, 20, y);
        y += 30;
        gfx->DrawString(this->txtDescription->Text, font, brush, 20, y);
        y += 30;

        Bitmap^ barcodeBitmap = GenerateBarcode(this->txtId->Text);
        gfx->DrawImage(barcodeBitmap, 20, y, 250, 100);
	}

	void MakeNewBaggageForm::btnMakeTag_Click(Object^ sender, EventArgs^ e)
	{
        if (String::IsNullOrWhiteSpace(this->txtId->Text) ||
            String::IsNullOrWhiteSpace(this->txtPassId->Text) ||
            String::IsNullOrWhiteSpace(this->txtWeight->Text) ||
            this->cmbDescription->SelectedItem == nullptr)
        {
            MessageBox::Show("Все поля должны быть заполнены.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
            return;
        }

        PrintDocument^ printDoc = gcnew PrintDocument();
        String^ pdfPath = Path::Combine(Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments), "AirplaneTag.pdf");

        printDoc->PrinterSettings->PrinterName = "Microsoft Print to PDF";
        printDoc->PrinterSettings->PrintToFile = true;
        printDoc->PrinterSettings->PrintFileName = pdfPath;

        printDoc->PrintPage += gcnew PrintPageEventHandler(this, &MakeNewBaggageForm::PrintPage);

        printDoc->Print();

        if (File::Exists(pdfPath))
        {
            Process::Start(pdfPath);
        }

        this->Close();
	}

    int MakeNewBaggageForm::GetNextBaggageId()
    {
        SqlConnection^ connection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");
        connection->Open();

        String^ query = "SELECT MAX(Id) FROM Багаж";
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

    Bitmap^ MakeNewBaggageForm::GenerateBarcode(String^ data)
    {
        BarcodeWriter^ writer = gcnew BarcodeWriter();

        writer->Format = BarcodeFormat::CODE_128;

        writer->Options = gcnew EncodingOptions();
        writer->Options->Height = 100;
        writer->Options->Width = 250;
        writer->Options->Margin = 1;

        writer->Renderer = gcnew ZXing::Rendering::BitmapRenderer();
        return writer->Write(data);
    }
}
