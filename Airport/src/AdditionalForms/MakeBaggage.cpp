#include "MakeBaggage.h"

namespace Airport
{
    MakeBaggageForm::MakeBaggageForm(String^ id, String^ talon, String^ weight, String^ dicr)
    {
        InitializeComponent(id, talon, weight, dicr);
    }

    MakeBaggageForm::~MakeBaggageForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void MakeBaggageForm::InitializeComponent(String^ id, String^ talon, String^ weight, String^ dicr)
    {
        this->components = gcnew System::ComponentModel::Container();
        System::Drawing::Icon^ icon = gcnew System::Drawing::Icon("main_logo.ico");
        this->Icon = icon;
        this->Text = "Багажная бирка";
        this->StartPosition = FormStartPosition::CenterScreen;

        printDoc = gcnew PrintDocument();
        printDoc->PrintPage += gcnew PrintPageEventHandler(this, &MakeBaggageForm::PrintPage);

        int leftMargin = 20;
        int topMargin = 20;
        int controlHeight = 40;
        int verticalSpacing = 10;

        this->txtId = gcnew MaterialSingleLineTextField();
        this->txtPassId = gcnew MaterialSingleLineTextField();
        this->txtWeight = gcnew MaterialSingleLineTextField();
        this->txtDescription= gcnew ComboBox();

        this->txtDescription->Items->Add("Спортивный инвентарь");
        this->txtDescription->Items->Add("Дипломатический");
        this->txtDescription->Items->Add("Стандартный багаж");
        this->txtDescription->Items->Add("Ручная кладь");

        this->txtPassId->Text = talon;
        this->txtId->Text = id;
        this->txtWeight->Text = weight;

        if (String::IsNullOrEmpty(dicr))

        {
            this->txtDescription->SelectedItem = "Стандартный багаж";
        }
        else
        {
            this->txtDescription->Text = dicr; 
        }

        this->txtId->Location = System::Drawing::Point(leftMargin + 90, topMargin);
        this->txtPassId->Location = System::Drawing::Point(leftMargin + 90, topMargin + controlHeight + verticalSpacing);
        this->txtWeight->Location = System::Drawing::Point(leftMargin + 90, topMargin + 2 * (controlHeight + verticalSpacing));
        this->txtDescription->Location = System::Drawing::Point(leftMargin, topMargin + 3 * (controlHeight + verticalSpacing));

        this->txtId->Size = System::Drawing::Size(120, controlHeight);
        this->txtPassId->Size = System::Drawing::Size(120, controlHeight);
        this->txtWeight->Size = System::Drawing::Size(120, controlHeight);
        this->txtDescription->Size = System::Drawing::Size(250, controlHeight);

        this->Controls->Add(this->txtId);
        this->Controls->Add(this->txtPassId);
        this->Controls->Add(this->txtWeight);
        this->Controls->Add(this->txtDescription);

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
        this->btnAdd->Text = "Изменить";
        this->btnAdd->Click += gcnew EventHandler(this, &MakeBaggageForm::btnAdd_Click);
        this->btnAdd->Location = System::Drawing::Point(leftMargin, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnAdd->Size = System::Drawing::Size(120, controlHeight);

        this->btnMakeTag = gcnew MaterialFlatButton();
        this->btnMakeTag->Text = "Печать";
        this->btnMakeTag->Location = System::Drawing::Point(leftMargin + 150, topMargin + 4 * (controlHeight + verticalSpacing));
        this->btnMakeTag->Size = System::Drawing::Size(120, controlHeight);
        this->btnMakeTag->Click += gcnew EventHandler(this, &MakeBaggageForm::btnMakeTag_Click);

        this->Controls->Add(this->btnAdd);
        this->Controls->Add(this->btnMakeTag);
    }

    void MakeBaggageForm::PrintPage(Object^ sender, PrintPageEventArgs^ e)
    {
        Graphics^ gfx = e->Graphics;
        System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 14);
        System::Drawing::Font^ font2 = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
        Brush^ brush = Brushes::Black;
        Pen^ pen = gcnew Pen(Color::Black, 2);
        System::Drawing::Font^ titleFont = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);
        SolidBrush^ titleBrush = gcnew SolidBrush(Color::DarkBlue);
        SolidBrush^ textBrush = gcnew SolidBrush(Color::Black);

        int y = 20;

        gfx->DrawRectangle(pen, 10, 10, 300, 500);

        gfx->DrawString("Багажная бирка", titleFont, titleBrush, 20, y);
        y += 40;

        gfx->DrawLine(pen, 20, y, 280, y);
        y += 20;

        gfx->DrawString("Номер бирки: " + this->txtId->Text, font2, brush, 20, y);
        y += 30;

        gfx->DrawString("Номер талона: " + this->txtPassId->Text, font, textBrush, 20, y);
        y += 30;

        gfx->DrawString("Вес: " + this->txtWeight->Text, font, textBrush, 20, y);
        y += 30;

        gfx->DrawString("Описание: " + this->txtDescription->Text, font, textBrush, 20, y);
        y += 30;

        gfx->DrawLine(pen, 20, y, 280, y);
        y += 20;

        Bitmap^ barcodeBitmap = GenerateBarcode(this->txtId->Text);
        gfx->DrawImage(barcodeBitmap, 20, y, 250, 100);
        y += 120;

        gfx->DrawImage(barcodeBitmap, 25, y + 5, 250, 100);


        gfx->DrawLine(pen, 20, y + 100, 280, y + 100);

    }

    void MakeBaggageForm::btnMakeTag_Click(Object^ sender, EventArgs^ e)
    {
        //if (String::IsNullOrWhiteSpace(this->txtId->Text) || String::IsNullOrWhiteSpace(this->txtPassId->Text) || this->cmbDescription->SelectedItem == nullptr)
        //{
        //    MessageBox::Show("Все поля должны быть заполнены.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        //    return;
        //}

        PrintDocument^ printDoc = gcnew PrintDocument();
        String^ pdfPath = Path::Combine(Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments), "AirplaneTag.pdf");

        printDoc->PrinterSettings->PrinterName = "Microsoft Print to PDF";
        printDoc->PrinterSettings->PrintToFile = true;
        printDoc->PrinterSettings->PrintFileName = pdfPath;

        printDoc->PrintPage += gcnew PrintPageEventHandler(this, &MakeBaggageForm::PrintPage);

        printDoc->Print();

        if (File::Exists(pdfPath))
        {
            Process::Start(pdfPath);
        }

        this->Close();
    }

    void MakeBaggageForm::btnAdd_Click(Object^ sender, EventArgs^ e)
    {
        String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
        SqlConnection^ connection = gcnew SqlConnection(connectionString);

        try
        {
            connection->Open();

            SqlCommand^ command = gcnew SqlCommand("UpdateBaggageTag", connection);
            command->CommandType = CommandType::StoredProcedure;

            command->Parameters->AddWithValue("@Id", Int32::Parse(this->txtId->Text));
            command->Parameters->AddWithValue("@IdТалона", Int32::Parse(this->txtPassId->Text));
            command->Parameters->AddWithValue("@Описание", this->txtDescription->SelectedItem->ToString());
            command->Parameters->AddWithValue("@Вес", Int32::Parse(this->txtWeight->Text));;

            SqlParameter^ outputMessage = gcnew SqlParameter("@message", SqlDbType::VarChar, 100);
            outputMessage->Direction = ParameterDirection::Output;
            command->Parameters->Add(outputMessage);

            command->ExecuteNonQuery();

            String^ message = outputMessage->Value->ToString();
            MessageBox::Show(message, "Операция выполнена", MessageBoxButtons::OK, MessageBoxIcon::Information);

            for each (Form ^ frm in Application::OpenForms)
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
        catch (SqlException^ ex)
        {
            MessageBox::Show("Ошибка изменения бирки: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        catch (Exception^ ex)
        {
            MessageBox::Show("Ошибка: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        finally
        {
            if (connection->State == ConnectionState::Open)
            {
                connection->Close();
            }
        }
    }

    Bitmap^ MakeBaggageForm::GenerateBarcode(String^ data)
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
