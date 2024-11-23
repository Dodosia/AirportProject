#include "Airports.h"

namespace Airport
{
	AirportsForm::AirportsForm()
	{
        InitializeComponent();
        loadAirports();

	}

	AirportsForm::~AirportsForm()
	{
		if (components)
		{
			delete components;
		}
	}

	void AirportsForm::InitializeComponent(void)
	{
        this->components = gcnew System::ComponentModel::Container();
        this->BackColor = System::Drawing::Color::White;
        int rightMargin = 20;
        int bottomMargin = 20;
        this->dataGridViewAeroports = gcnew DataGridView();
        this->dataGridViewAeroports->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
        this->dataGridViewAeroports->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
        this->dataGridViewAeroports->DefaultCellStyle->BackColor = System::Drawing::Color::White;
        this->dataGridViewAeroports->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
        this->dataGridViewAeroports->ColumnHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->dataGridViewAeroports->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::White;
        this->dataGridViewAeroports->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
        this->dataGridViewAeroports->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
        this->dataGridViewAeroports->EnableHeadersVisualStyles = false;
        this->dataGridViewAeroports->GridColor = System::Drawing::Color::LightGray;
        this->dataGridViewAeroports->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
        this->dataGridViewAeroports->RowHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->dataGridViewAeroports->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->dataGridViewAeroports->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
        this->dataGridViewAeroports->Dock = System::Windows::Forms::DockStyle::Fill;
        this->dataGridViewAeroports->Margin = System::Windows::Forms::Padding(10);
        this->dataGridViewAeroports->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
        this->dataGridViewAeroports->BackgroundColor = System::Drawing::Color::White;
        this->dataGridViewAeroports->ForeColor = System::Drawing::Color::Black;
        this->dataGridViewAeroports->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        this->dataGridViewAeroports->Location = System::Drawing::Point(20, 80);
        this->dataGridViewAeroports->Size = System::Drawing::Size(this->ClientSize.Width - this->dataGridViewAeroports->Location.X - rightMargin, this->ClientSize.Height - this->dataGridViewAeroports->Location.Y - bottomMargin);
        this->dataGridViewAeroports->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
        this->dataGridViewAeroports->Columns->Add("Код", "Номер");
        this->dataGridViewAeroports->Columns->Add("Страна", "Id Самолета");
        this->dataGridViewAeroports->Columns->Add("Город", "Аэропорт вылета");
        this->dataGridViewAeroports->ReadOnly = true;
        this->Controls->Add(this->dataGridViewAeroports);

        this->txtNumber = gcnew MaterialSingleLineTextField();
        this->txtNumber->Hint = "Код";
        this->txtNumber->BackColor = System::Drawing::Color::Blue;
        this->txtNumber->ForeColor = System::Drawing::Color::Black;
        this->txtNumber->Location = System::Drawing::Point(350, 20);
        this->txtNumber->Size = System::Drawing::Size(300, 20);
        this->Controls->Add(this->txtNumber);

        this->txtAirport = gcnew MaterialSingleLineTextField();
        this->txtAirport->Hint = "Страна";
        this->txtAirport->BackColor = System::Drawing::Color::Blue;
        this->txtAirport->ForeColor = System::Drawing::Color::Black;
        this->txtAirport->Location = System::Drawing::Point(20, 20);
        this->txtAirport->Size = System::Drawing::Size(300, 20);
        this->Controls->Add(this->txtAirport);

        this->txtTown = gcnew MaterialSingleLineTextField();
        this->txtTown->Hint = "Город";
        this->txtTown->BackColor = System::Drawing::Color::Blue;
        this->txtTown->ForeColor = System::Drawing::Color::Black;
        this->txtTown->Location = System::Drawing::Point(700, 20);
        this->txtTown->Size = System::Drawing::Size(300, 20);
        this->Controls->Add(this->txtTown);

        this->btnSearch = gcnew MaterialFlatButton();
        this->btnSearch->Text = "Найти";
        this->btnSearch->Location = System::Drawing::Point(1020, 15);
        this->Controls->Add(this->btnSearch);
	}

	void AirportsForm::loadAirports()
	{
        dataGridViewAeroports->Rows->Clear();

        String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
        sqlConnection = gcnew SqlConnection(connectionString);
        SqlCommand^ command = gcnew SqlCommand("SELECT * FROM Аэропорт", sqlConnection);

        sqlConnection->Open();
        SqlDataReader^ reader = command->ExecuteReader();

        while (reader->Read())
        {
            dataGridViewAeroports->Rows->Add(
                reader["Код"]->ToString(),
                reader["Страна"]->ToString(),
                reader["Город"]->ToString()
            );
        }

        reader->Close();
	}
}
