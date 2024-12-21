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
		this->dataGridViewTickets->CellDoubleClick += gcnew DataGridViewCellEventHandler(this, &TicketsForm::dataGridViewTickets_CellClick);

		this->Controls->Add(this->dataGridViewTickets);

		this->txtId = gcnew MaterialSingleLineTextField();
		this->txtId->Hint = "Номер билета";
		this->txtId->ForeColor = System::Drawing::Color::Black;
		this->txtId->Location = System::Drawing::Point(20, 20);
		this->txtId->Size = System::Drawing::Size(250, 20);
		this->Controls->Add(this->txtId);

		this->txtPasId = gcnew MaterialSingleLineTextField();
		this->txtPasId->Hint = "Id пассажира";
		this->txtPasId->ForeColor = System::Drawing::Color::Black;
		this->txtPasId->Location = System::Drawing::Point(txtId->Right + 20, 20);
		this->txtPasId->Size = System::Drawing::Size(250, 20);
		this->Controls->Add(this->txtPasId);

		this->txtFlight = gcnew MaterialSingleLineTextField();
		this->txtFlight->Hint = "Номер рейса";
		this->txtFlight->ForeColor = System::Drawing::Color::Black;
		this->txtFlight->Location = System::Drawing::Point(txtPasId->Right + 20, 20);
		this->txtFlight->Size = System::Drawing::Size(250, 20);
		this->Controls->Add(this->txtFlight);

		this->txtDate = gcnew MaterialSingleLineTextField();
		this->txtDate->Hint = "Дата отправления";
		this->txtDate->ForeColor = System::Drawing::Color::Black;
		this->txtDate->Location = System::Drawing::Point(txtFlight->Right + 20, 20);
		this->txtDate->Size = System::Drawing::Size(250, 20);
		this->Controls->Add(this->txtDate);

		this->btnSearch = gcnew MaterialFlatButton();
		this->btnSearch->Text = "Найти";
		this->btnSearch->Location = System::Drawing::Point(txtDate->Right + 20, 15);
		this->btnSearch->Click += gcnew System::EventHandler(this, &TicketsForm::btnSearch_Click);
		this->Controls->Add(this->btnSearch);

		this->btnClear = gcnew MaterialFlatButton();
		this->btnClear->Text = "Очистить";
		this->btnClear->Location = System::Drawing::Point(btnSearch->Right + 20, 15);
		this->btnClear->Click += gcnew System::EventHandler(this, &TicketsForm::btnClear_Click);
		this->Controls->Add(this->btnClear);
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

	void TicketsForm::btnSearch_Click(System::Object^ sender, System::EventArgs^ e)
	{
		dataGridViewTickets->Rows->Clear();  // Очищаем текущие строки в таблице

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);

		String^ query = "SELECT * FROM Билет WHERE 1 = 1";

		if (!String::IsNullOrEmpty(txtId->Text))
		{
			query += " AND Номер = @Номер";
		}
		if (!String::IsNullOrEmpty(txtPasId->Text))
		{
			query += " AND IdПассажира = @IdПассажира";
		}
		if (!String::IsNullOrEmpty(txtFlight->Text))
		{
			query += " AND НомерРейса = @НомерРейса";
		}
		if (!String::IsNullOrEmpty(txtDate->Text))
		{
			query += " AND ДатаОтправления = @ДатаОтправления";
		}

		SqlCommand^ command = gcnew SqlCommand(query, sqlConnection);

		if (!String::IsNullOrEmpty(txtId->Text))
		{
			command->Parameters->AddWithValue("@Номер", txtId->Text);
		}
		if (!String::IsNullOrEmpty(txtPasId->Text))
		{
			command->Parameters->AddWithValue("@IdПассажира", txtPasId->Text);
		}
		if (!String::IsNullOrEmpty(txtFlight->Text))
		{
			command->Parameters->AddWithValue("@НомерРейса", txtFlight->Text);
		}
		if (!String::IsNullOrEmpty(txtDate->Text))
		{
			command->Parameters->AddWithValue("@ДатаОтправления", txtDate->Text);
		}

		bool found = false;

		try
		{
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
				found = true;
			}

			reader->Close();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Ошибка при выполнении запроса: " + ex->Message);
		}
		finally
		{
			sqlConnection->Close();
		}

		if (!found)
		{
			LoadTickets();
			MessageBox::Show("Билет, соответствующий заданным параметрам, не найден.", "Поиск не дал результатов", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}

	void TicketsForm::btnClear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		txtId->Clear();
		txtPasId->Clear();
		txtFlight->Clear();
		txtDate->Clear();

		dataGridViewTickets->Rows->Clear();
		LoadTickets();
	}

	void TicketsForm::dataGridViewTickets_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		if (e->RowIndex < 0) return;

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);

		String^ ticketId = (dataGridViewTickets->Rows[e->RowIndex]->Cells["Номер"]->Value)->ToString();

		Form^ makePassForm = gcnew MakeNewPassForm(ticketId);
		makePassForm->Show();
	}
}
