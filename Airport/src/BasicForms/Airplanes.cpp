#include "Airplanes.h"

namespace Airport
{
    AirplanesForm::AirplanesForm()
    {
        InitializeComponent();
        LoadAirplanes();
    }

    AirplanesForm::~AirplanesForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void AirplanesForm::InitializeComponent(void)
    {
		this->components = gcnew System::ComponentModel::Container();
		this->BackColor = System::Drawing::Color::White;

		int rightMargin = 20;
		int bottomMargin = 20;
		this->dataGridViewAirplanes = gcnew DataGridView();
		this->dataGridViewAirplanes->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
		this->dataGridViewAirplanes->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
		this->dataGridViewAirplanes->DefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewAirplanes->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewAirplanes->ColumnHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewAirplanes->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewAirplanes->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewAirplanes->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
		this->dataGridViewAirplanes->EnableHeadersVisualStyles = false;
		this->dataGridViewAirplanes->GridColor = System::Drawing::Color::LightGray;
		this->dataGridViewAirplanes->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dataGridViewAirplanes->RowHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewAirplanes->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewAirplanes->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
		this->dataGridViewAirplanes->Dock = System::Windows::Forms::DockStyle::Fill;
		this->dataGridViewAirplanes->Margin = System::Windows::Forms::Padding(10);
		this->dataGridViewAirplanes->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
		this->dataGridViewAirplanes->BackgroundColor = System::Drawing::Color::White;
		this->dataGridViewAirplanes->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewAirplanes->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		this->dataGridViewAirplanes->Location = System::Drawing::Point(20, 80);
		this->dataGridViewAirplanes->Size = System::Drawing::Size(this->ClientSize.Width - this->dataGridViewAirplanes->Location.X - rightMargin, this->ClientSize.Height - this->dataGridViewAirplanes->Location.Y - bottomMargin);
		this->dataGridViewAirplanes->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
		this->dataGridViewAirplanes->Columns->Add("Id", "Id");
		this->dataGridViewAirplanes->Columns->Add("Модель", "Модель");
		this->dataGridViewAirplanes->Columns->Add("Вместимость", "Вместимость");
		this->dataGridViewAirplanes->Columns->Add("ВесБагажа", "Вес багажа");
		this->dataGridViewAirplanes->Columns->Add("ГодВводаВЭксплуатацию", "Год ввода в эксплуатацию");

		this->Controls->Add(this->dataGridViewAirplanes);

		this->txtModel = gcnew MaterialSingleLineTextField();
		this->txtModel->Hint = "Модель самолета";
		this->txtModel->ForeColor = System::Drawing::Color::Black;
		this->txtModel->Location = System::Drawing::Point(20, 20);
		this->txtModel->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtModel);

		this->txtYear = gcnew MaterialSingleLineTextField();
		this->txtYear->Hint = "Год ввода в эксплуатацию";
		this->txtYear->ForeColor = System::Drawing::Color::Black;
		this->txtYear->Location = System::Drawing::Point(370, 20);
		this->txtYear->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtYear);

		this->btnSearch = gcnew MaterialFlatButton();
		this->btnSearch->Text = "Найти";
		this->btnSearch->Location = System::Drawing::Point(720, 15);
		this->Controls->Add(this->btnSearch);
    }

    void AirplanesForm::LoadAirplanes()
    {
		dataGridViewAirplanes->Rows->Clear();

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand("SELECT * FROM Самолет", sqlConnection);

		sqlConnection->Open();
		SqlDataReader^ reader = command->ExecuteReader();

		while (reader->Read())
		{
			dataGridViewAirplanes->Rows->Add(
				reader["Id"]->ToString(),
				reader["Модель"]->ToString(),
				reader["Вместимость"]->ToString(),
				reader["ВесБагажа"]->ToString(),
				reader["ГодВводаВЭксплуатацию"]->ToString()
			);
		}

		reader->Close();
		sqlConnection->Close();
    }
}
