#include "AirplaneReport.h"

namespace Airport
{
    AirplaneReportForm::AirplaneReportForm(String^ airplaneId, String^ model, String^ capacity, String^ baggageWeight, String^ year) : 
        _airplaneId(airplaneId), _model(model), _capacity(capacity), _baggageWeight(baggageWeight), _year(year)
    {
        InitializeComponent();
    }

    AirplaneReportForm::~AirplaneReportForm()
    {
        
    }

    void AirplaneReportForm::InitializeComponent()
    {
        this->Text = "Отчет по самолету";
        this->Size = System::Drawing::Size(800, 600);
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;

        int labelY = 10;
        int labelX = 10;
        int labelWidth = 300;
        int labelHeight = 25;
        System::Drawing::Font^ labelFont = gcnew System::Drawing::Font("Arial", 12);

        Label^ text = gcnew Label();
        text->Text = "ПРОВЕДЕНИЕ ОСМОТРА";
        text->Dock = DockStyle::Top;
        text->Location = System::Drawing::Point(0, 0);
        text->Size = System::Drawing::Size(800, 30);
        text->Font = gcnew System::Drawing::Font("Roboto", 14, System::Drawing::FontStyle::Bold);
        text->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);
        text->BackColor = System::Drawing::Color::FromArgb(55, 71, 79);
        text->ForeColor = System::Drawing::Color::White;
        text->TextAlign = ContentAlignment::MiddleCenter;
        this->Controls->Add(text);

        this->dataGridView = gcnew System::Windows::Forms::DataGridView();
        this->dataGridView->Location = System::Drawing::Point(10, text->Bottom + 20);
        this->dataGridView->Size = System::Drawing::Size(760, 350);
        this->dataGridView->ColumnCount = 2;
        this->dataGridView->Columns[0]->Name = "Компонент";
        this->dataGridView->Columns[1]->Name = "Состояние";
        this->dataGridView->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        this->dataGridView->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
        this->dataGridView->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
        this->dataGridView->DefaultCellStyle->BackColor = System::Drawing::Color::White;
        this->dataGridView->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
        this->dataGridView->ColumnHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->dataGridView->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::White;
        this->dataGridView->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
        this->dataGridView->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
        this->dataGridView->EnableHeadersVisualStyles = false;
        this->dataGridView->GridColor = System::Drawing::Color::LightGray;
        this->dataGridView->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
        this->dataGridView->RowHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->dataGridView->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->dataGridView->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
        this->dataGridView->Margin = System::Windows::Forms::Padding(10);
        this->dataGridView->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
        this->dataGridView->BackgroundColor = System::Drawing::Color::White;
        this->dataGridView->ForeColor = System::Drawing::Color::Black;
        this->dataGridView->RowTemplate->Height = 40;

        System::Windows::Forms::DataGridViewComboBoxColumn^ conditionColumn = gcnew System::Windows::Forms::DataGridViewComboBoxColumn();
        conditionColumn->Name = "Состояние";
        conditionColumn->Items->AddRange(gcnew cli::array<String^> { "Исправно", "Требует ремонта" });
        conditionColumn->Width = 360;
        this->dataGridView->Columns->RemoveAt(1);
        this->dataGridView->Columns->Add(conditionColumn);

        array<String^>^ airplaneParts = {
            "Фюзеляж",
            "Крылья",
            "Двигатели",
            "Шасси",
            "Хвостовая часть",
            "Кислородная система",
            "Система торможения",
            "Хвостовой стабилизатор"
        };

        for each (String ^ part in airplaneParts)
        {
            this->dataGridView->Rows->Add(part, "Исправно");
        }

        this->Controls->Add(this->dataGridView);

        this->saveReportButton = gcnew MaterialRaisedButton();
        this->saveReportButton->Text = "Сохранить отчет";
        this->saveReportButton->Location = System::Drawing::Point(300, 500);
        this->saveReportButton->Size = System::Drawing::Size(200, 50);
        this->saveReportButton->Click += gcnew System::EventHandler(this, &AirplaneReportForm::saveReportButton_Click);
        this->Controls->Add(this->saveReportButton);

        this->fullNameTextBox = gcnew MaterialSingleLineTextField();
        this->fullNameTextBox->Hint = "ФИО проверяющего";
        this->fullNameTextBox->Location = System::Drawing::Point(labelX, this->dataGridView->Bottom + 40);
        this->fullNameTextBox->Size = System::Drawing::Size(755, labelHeight);
        this->fullNameTextBox->Font = labelFont;
        this->Controls->Add(this->fullNameTextBox);
    }

    void AirplaneReportForm::PrintPageHandler(System::Object^ sender, PrintPageEventArgs^ e)
    {
        Graphics^ gfx = e->Graphics;
        System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 14);
        System::Drawing::Font^ font2 = gcnew System::Drawing::Font("Arial", 14, FontStyle::Bold);
        Brush^ brush = Brushes::Black;
        Pen^ pen = gcnew Pen(Color::Black, 2);

        System::Drawing::Font^ titleFont = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);

        String^ title = "Отчет о самолете";
        int pageWidth = e->PageBounds.Width;
        SizeF titleSize = gfx->MeasureString(title, titleFont);
        float titleX = (pageWidth - titleSize.Width) / 2;

        int y = 20;

        gfx->DrawString(title, titleFont, brush, titleX, y);
        y += 50;

        gfx->DrawString("ID самолета: " + _airplaneId, font, brush, 20, y);
        y += 30;
        gfx->DrawString("Модель: " + _model, font, brush, 20, y);
        y += 30;
        gfx->DrawString("Вместимость: " + _capacity, font, brush, 20, y);
        y += 30;
        gfx->DrawString("Вес багажа: " + _baggageWeight, font, brush, 20, y);
        y += 30;
        gfx->DrawString("Год выпуска: " + _year, font, brush, 20, y);
        y += 40;

        int startX = 20;
        int rowHeight = 30;
        int col1Width = 350; 
        int col2Width = 200;  

        gfx->DrawRectangle(pen, startX, y, col1Width, rowHeight);
        gfx->DrawRectangle(pen, startX + col1Width, y, col2Width, rowHeight);
        gfx->DrawString("Компонент", font2, brush, startX + 5, y + 5);
        gfx->DrawString("Состояние", font2, brush, startX + col1Width + 5, y + 5);

        y += rowHeight; 

        for (int i = 0; i < this->dataGridView->Rows->Count; ++i)
        {
            if (this->dataGridView->Rows[i]->IsNewRow)
                continue;

            String^ part = this->dataGridView->Rows[i]->Cells[0]->Value != nullptr ?
                this->dataGridView->Rows[i]->Cells[0]->Value->ToString() : "N/A";

            String^ condition = this->dataGridView->Rows[i]->Cells[1]->Value != nullptr ?
                this->dataGridView->Rows[i]->Cells[1]->Value->ToString() : "N/A";

            Brush^ conditionBrush;
            if (condition == "Исправно")
            {
                conditionBrush = Brushes::Green;
            }
            else if (condition == "Требует ремонта")
            {
                conditionBrush = Brushes::Red;
            }
            else
            {
                conditionBrush = brush;
            }

            gfx->DrawRectangle(pen, startX, y, col1Width, rowHeight);
            gfx->DrawRectangle(pen, startX + col1Width, y, col2Width, rowHeight);

            gfx->DrawString(part, font, brush, startX + 5, y + 5);  // Обычный цвет
            gfx->DrawString(condition, font, conditionBrush, startX + col1Width + 5, y + 5);  // Цвет состояния

            y += rowHeight;
        }

        y += 40;
        String^ inspectorName = this->fullNameTextBox->Text;
        date = DateTime::Now.ToString("dd.MM.yyyy");

        gfx->DrawString("Проверяющий: " + inspectorName, font, brush, 20, y);
        y += 30;
        gfx->DrawString("Дата осмотра: " + date, font, brush, 20, y);
    }

    void AirplaneReportForm::saveReportButton_Click(System::Object^ sender, System::EventArgs^ e)
    {
        PrintDocument^ printDoc = gcnew PrintDocument();
        String^ pdfPath = Path::Combine(Environment::GetFolderPath(Environment::SpecialFolder::MyDocuments), "AirplaneReport.pdf");

        printDoc->PrinterSettings->PrinterName = "Microsoft Print to PDF";
        printDoc->PrinterSettings->PrintToFile = true;
        printDoc->PrinterSettings->PrintFileName = pdfPath;

        printDoc->PrintPage += gcnew PrintPageEventHandler(this, &AirplaneReportForm::PrintPageHandler);
        printDoc->Print();

        if (File::Exists(pdfPath))
        {
            Process::Start(pdfPath);
        }

        SqlConnection^ connection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");
        connection->Open();

        // Получение текущей даты и времени
        DateTime currentDateTime = DateTime::Now;

        SqlCommand^ command = gcnew SqlCommand("UpdateLastServiceDate", connection);
        command->CommandType = CommandType::StoredProcedure;

        command->Parameters->AddWithValue("@AirplaneId", Convert::ToInt32(_airplaneId));
        command->Parameters->AddWithValue("@LastServiceDate", currentDateTime); // Передача даты и времени

        command->ExecuteNonQuery();
        MessageBox::Show("Дата и время последнего обслуживания успешно обновлены.", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);
        connection->Close();

        for each (Form ^ frm in Application::OpenForms)
        {
            if (frm->Name == "MenuTechForm")
            {
                MenuTechForm^ menuForm = dynamic_cast<MenuTechForm^>(frm);
                if (menuForm != nullptr)
                {
                    for each (Control ^ control in menuForm->airplaneTab->Controls)
                    {
                        AirplanesForm^ boardingPassForm = dynamic_cast<AirplanesForm^>(control);
                        if (boardingPassForm != nullptr)
                        {
                            boardingPassForm->LoadAirplanes();
                        }
                    }
                }
            }
        }

        this->Close();
    }
}
