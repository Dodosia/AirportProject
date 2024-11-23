#include "Tickets.h"

namespace Airport
{
	TicketsForm::TicketsForm()
	{
		InitializeComponent();
		LoadTickets();
	}

	TicketsForm::~TicketsForm()
	{
		if (components)
		{
			delete components;
		}
	}

	void TicketsForm::InitializeComponent(void)
	{
		this->components = gcnew System::ComponentModel::Container();

		this->BackColor = System::Drawing::Color::White;

		int rightMargin = 20;
		int bottomMargin = 20;
		this->dataGridViewTickets = gcnew DataGridView();
		this->dataGridViewTickets->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
		this->dataGridViewTickets->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
		this->dataGridViewTickets->DefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewTickets->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewTickets->ColumnHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewTickets->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewTickets->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewTickets->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
		this->dataGridViewTickets->EnableHeadersVisualStyles = false;
		this->dataGridViewTickets->GridColor = System::Drawing::Color::LightGray;
		this->dataGridViewTickets->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dataGridViewTickets->RowHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewTickets->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewTickets->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
		this->dataGridViewTickets->Dock = System::Windows::Forms::DockStyle::Fill;
		this->dataGridViewTickets->Margin = System::Windows::Forms::Padding(10);
		this->dataGridViewTickets->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
		this->dataGridViewTickets->BackgroundColor = System::Drawing::Color::White;
		this->dataGridViewTickets->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewTickets->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		this->dataGridViewTickets->Location = System::Drawing::Point(20, 80);
		this->dataGridViewTickets->Size = System::Drawing::Size(this->ClientSize.Width - this->dataGridViewTickets->Location.X - rightMargin, this->ClientSize.Height - this->dataGridViewTickets->Location.Y - bottomMargin);
		this->dataGridViewTickets->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
		this->dataGridViewTickets->Columns->Add("Номер", "Номер билета");
		this->dataGridViewTickets->Columns->Add("IdПассажира", "Id пассажира");
		this->dataGridViewTickets->Columns->Add("НомерРейса", "Номер рейса");
		this->dataGridViewTickets->Columns->Add("ДатаОтправления", "Дата отправления");
		this->dataGridViewTickets->Columns->Add("Класс", "Класс");
		this->dataGridViewTickets->ReadOnly = true;

		this->Controls->Add(this->dataGridViewTickets);

		this->txtId = gcnew MaterialSingleLineTextField();
		this->txtId->Hint = "Номер билета";
		this->txtId->ForeColor = System::Drawing::Color::Black;
		this->txtId->Location = System::Drawing::Point(20, 20);
		this->txtId->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtId);

		this->txtPasId = gcnew MaterialSingleLineTextField();
		this->txtPasId->Hint = "Id пассажира";
		this->txtPasId->ForeColor = System::Drawing::Color::Black;
		this->txtPasId->Location = System::Drawing::Point(370, 20);
		this->txtPasId->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtPasId);

		this->txtFlight = gcnew MaterialSingleLineTextField();
		this->txtFlight->Hint = "Номер рейса";
		this->txtFlight->ForeColor = System::Drawing::Color::Black;
		this->txtFlight->Location = System::Drawing::Point(720, 20);
		this->txtFlight->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtFlight);

		this->txtDate = gcnew MaterialSingleLineTextField();
		this->txtDate->Hint = "Дата отправления";
		this->txtDate->ForeColor = System::Drawing::Color::Black;
		this->txtDate->Location = System::Drawing::Point(1070, 20);
		this->txtDate->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtDate);

		this->btnSearch = gcnew MaterialFlatButton();
		this->btnSearch->Text = "Найти";
		this->btnSearch->Location = System::Drawing::Point(1400, 15);
		this->Controls->Add(this->btnSearch);

	}

	void TicketsForm::LoadTickets()
	{
		dataGridViewTickets->Rows->Clear();

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand("SELECT * FROM Билет", sqlConnection);

		sqlConnection->Open();
		SqlDataReader^ reader = command->ExecuteReader();

		while (reader->Read())
		{
			dataGridViewTickets->Rows->Add(
				reader["Номер"]->ToString(),
				reader["IdПассажира"]->ToString(),
				reader["НомерРейса"]->ToString(),
				reader["ДатаОтправления"]->ToString(),
				reader["Класс"]->ToString()
			);
		}

		reader->Close();
		sqlConnection->Close();
	}
}
