#include "Passangers.h"

namespace Airport
{
	PassangersForm::PassangersForm(void)
	{
		InitializeComponent();
		LoadPassangers();
	}

	PassangersForm::~PassangersForm()
	{
		if (components)
		{
			delete components;
		}
	}

	void PassangersForm::InitializeComponent(void)
	{
		this->components = gcnew System::ComponentModel::Container();
		this->BackColor = System::Drawing::Color::White;

		int rightMargin = 20;
		int bottomMargin = 20;
		this->dataGridViewPassangers = gcnew DataGridView();
		this->dataGridViewPassangers->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
		this->dataGridViewPassangers->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
		this->dataGridViewPassangers->DefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewPassangers->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewPassangers->ColumnHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewPassangers->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewPassangers->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewPassangers->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
		this->dataGridViewPassangers->EnableHeadersVisualStyles = false;
		this->dataGridViewPassangers->GridColor = System::Drawing::Color::LightGray;
		this->dataGridViewPassangers->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dataGridViewPassangers->RowHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewPassangers->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewPassangers->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
		this->dataGridViewPassangers->Dock = System::Windows::Forms::DockStyle::Fill;
		this->dataGridViewPassangers->Margin = System::Windows::Forms::Padding(10);
		this->dataGridViewPassangers->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
		this->dataGridViewPassangers->BackgroundColor = System::Drawing::Color::White;
		this->dataGridViewPassangers->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewPassangers->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		this->dataGridViewPassangers->Location = System::Drawing::Point(20, 80);
		this->dataGridViewPassangers->Size = System::Drawing::Size(this->ClientSize.Width - this->dataGridViewPassangers->Location.X - rightMargin, this->ClientSize.Height - this->dataGridViewPassangers->Location.Y - bottomMargin);
		this->dataGridViewPassangers->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
		this->dataGridViewPassangers->Columns->Add("Id", "Id");
		this->dataGridViewPassangers->Columns->Add("Фио", "Фио");
		this->dataGridViewPassangers->Columns->Add("Паспорт", "Номер паспорта");
		this->dataGridViewPassangers->Columns->Add("ДатаРождения", "Дата рождения");
		this->dataGridViewPassangers->Columns->Add("Пол", "Пол");
		this->dataGridViewPassangers->Columns->Add("Телефон", "Телефон");
		this->dataGridViewPassangers->ReadOnly = true;

		this->Controls->Add(this->dataGridViewPassangers);

		this->txtFio = gcnew MaterialSingleLineTextField();
		this->txtFio->Hint = "ФИО";
		this->txtFio->ForeColor = System::Drawing::Color::Black;
		this->txtFio->Location = System::Drawing::Point(20, 20);
		this->txtFio->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtFio);

		this->txtPassport = gcnew MaterialSingleLineTextField();
		this->txtPassport->Hint = "Номер паспорта";
		this->txtPassport->ForeColor = System::Drawing::Color::Black;
		this->txtPassport->Location = System::Drawing::Point(370, 20);
		this->txtPassport->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtPassport);

		this->txtPhone = gcnew MaterialSingleLineTextField();
		this->txtPhone->Hint = "Номер телефона";
		this->txtPhone->ForeColor = System::Drawing::Color::Black;
		this->txtPhone->Location = System::Drawing::Point(720, 20);
		this->txtPhone->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtPhone);

		this->btnSearch = gcnew MaterialFlatButton();
		this->btnSearch->Text = "Найти";
		this->btnSearch->Location = System::Drawing::Point(1070, 15);
		this->Controls->Add(this->btnSearch);
	}

	void PassangersForm::LoadPassangers()
	{
		dataGridViewPassangers->Rows->Clear();

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand("SELECT * FROM Пассажир", sqlConnection);

		sqlConnection->Open();
		SqlDataReader^ reader = command->ExecuteReader();

		while (reader->Read())
		{
			dataGridViewPassangers->Rows->Add(
				reader["Id"]->ToString(),
				reader["Фио"]->ToString(),
				reader["Паспорт"]->ToString(),
				reader["ДатаРождения"]->ToString(),
				reader["Пол"]->ToString(),
				reader["Телефон"]->ToString()
			);
		}

		reader->Close();
		sqlConnection->Close();
	}
}
