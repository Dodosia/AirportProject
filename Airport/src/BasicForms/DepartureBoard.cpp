#include "DepartureBoard.h"

namespace Airport
{
    DepartureBoardForm::DepartureBoardForm()
    {
        InitializeComponent();
        LoadFlights();
    }

    DepartureBoardForm::~DepartureBoardForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void DepartureBoardForm::InitializeComponent(void)
    {
		this->components = gcnew System::ComponentModel::Container();
		this->BackColor = System::Drawing::Color::White;

		int rightMargin = 20;
		int bottomMargin = 20;
		this->dataGridViewDepBoard = gcnew DataGridView();
		this->dataGridViewDepBoard->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
		this->dataGridViewDepBoard->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
		this->dataGridViewDepBoard->DefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewDepBoard->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewDepBoard->ColumnHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewDepBoard->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewDepBoard->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewDepBoard->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
		this->dataGridViewDepBoard->EnableHeadersVisualStyles = false;
		this->dataGridViewDepBoard->GridColor = System::Drawing::Color::LightGray;
		this->dataGridViewDepBoard->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dataGridViewDepBoard->RowHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewDepBoard->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewDepBoard->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
		this->dataGridViewDepBoard->Dock = System::Windows::Forms::DockStyle::Fill;
		this->dataGridViewDepBoard->Margin = System::Windows::Forms::Padding(10);
		this->dataGridViewDepBoard->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
		this->dataGridViewDepBoard->BackgroundColor = System::Drawing::Color::White;
		this->dataGridViewDepBoard->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewDepBoard->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		this->dataGridViewDepBoard->Location = System::Drawing::Point(20, 80);
		this->dataGridViewDepBoard->Size = System::Drawing::Size(this->ClientSize.Width - this->dataGridViewDepBoard->Location.X - rightMargin, this->ClientSize.Height - this->dataGridViewDepBoard->Location.Y - bottomMargin);
		this->dataGridViewDepBoard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
		this->dataGridViewDepBoard->Columns->Add("Id", "Id");
		this->dataGridViewDepBoard->Columns->Add("НомерРейса", "Номер рейса");
		this->dataGridViewDepBoard->Columns->Add("Время", "Время прибытия");
		this->dataGridViewDepBoard->Columns->Add("Статус", "Статус");
		for each (DataGridViewColumn ^ column in this->dataGridViewDepBoard->Columns)
		{
			column->ReadOnly = true;
		}
		this->dataGridViewDepBoard->Columns["Статус"]->ReadOnly = false;

		this->Controls->Add(this->dataGridViewDepBoard);

		this->txtFlight = gcnew MaterialSingleLineTextField();
		this->txtFlight->Hint = "Номер рейса";
		this->txtFlight->ForeColor = System::Drawing::Color::Black;
		this->txtFlight->Location = System::Drawing::Point(20, 20);
		this->txtFlight->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtFlight);

		this->btnSearch = gcnew MaterialFlatButton();
		this->btnSearch->Text = "Найти";
		this->btnSearch->Location = System::Drawing::Point(370, 15);
		this->Controls->Add(this->btnSearch);
    }

    void DepartureBoardForm::LoadFlights()
    {
		dataGridViewDepBoard->Rows->Clear();

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand("SELECT * FROM ТаблоВылета", sqlConnection);

		sqlConnection->Open();
		SqlDataReader^ reader = command->ExecuteReader();

		while (reader->Read())
		{
			dataGridViewDepBoard->Rows->Add(
				reader["Id"]->ToString(),
				reader["НомерРейса"]->ToString(),
				reader["Время"]->ToString(),
				reader["Статус"]->ToString()
			);
		}

		reader->Close();
		sqlConnection->Close();
    }
}
