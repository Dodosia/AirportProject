#include "ArrivalBoard.h"

namespace Airport
{
	ArrivalBoardForm::ArrivalBoardForm()
	{
		InitializeComponent();
		LoadFlights();
	}

	ArrivalBoardForm::~ArrivalBoardForm()
	{
		if (components)
		{
			delete components;
		}
	}

	void ArrivalBoardForm::InitializeComponent(void)
	{
		this->components = gcnew System::ComponentModel::Container();
		this->BackColor = System::Drawing::Color::White;

		int rightMargin = 20;
		int bottomMargin = 20;
		this->dataGridViewArBoard = gcnew DataGridView();
		this->dataGridViewArBoard->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
		this->dataGridViewArBoard->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
		this->dataGridViewArBoard->DefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewArBoard->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewArBoard->ColumnHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewArBoard->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewArBoard->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewArBoard->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
		this->dataGridViewArBoard->EnableHeadersVisualStyles = false;
		this->dataGridViewArBoard->GridColor = System::Drawing::Color::LightGray;
		this->dataGridViewArBoard->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dataGridViewArBoard->RowHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewArBoard->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewArBoard->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
		this->dataGridViewArBoard->Margin = System::Windows::Forms::Padding(10);
		this->dataGridViewArBoard->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
		this->dataGridViewArBoard->BackgroundColor = System::Drawing::Color::White;
		this->dataGridViewArBoard->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewArBoard->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		this->dataGridViewArBoard->Size = System::Drawing::Size(this->ClientSize.Width - 2 * rightMargin, 300);
		this->dataGridViewArBoard->Location = System::Drawing::Point(rightMargin, 80);
		this->dataGridViewArBoard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
		this->dataGridViewArBoard->RowTemplate->Height = 40;

		this->dataGridViewArBoard->Columns->Add("Id", "Id");
		this->dataGridViewArBoard->Columns->Add("НомерРейса", "Номер рейса");
		this->dataGridViewArBoard->Columns->Add("Время", "Время прибытия");

		DataGridViewComboBoxColumn^ comboBoxColumn = gcnew DataGridViewComboBoxColumn();
		comboBoxColumn->Name = "Статус";
		comboBoxColumn->HeaderText = "Статус";
		comboBoxColumn->DataSource = gcnew array<String^> { "Отменен", "Задержан", "Прибыл", "Посадка" };
		this->dataGridViewArBoard->Columns->Add(comboBoxColumn);

		this->dataGridViewArBoard->CellEndEdit += gcnew DataGridViewCellEventHandler(this, &ArrivalBoardForm::dataGridViewDepBoard_CellEndEdit);

		for each (DataGridViewColumn ^ column in this->dataGridViewArBoard->Columns)
		{
			column->ReadOnly = true;
		}
		this->dataGridViewArBoard->Columns["Статус"]->ReadOnly = false;

		this->Controls->Add(this->dataGridViewArBoard);

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

		LoadWebBrowser();
	}

	void ArrivalBoardForm::LoadFlights()
	{
		dataGridViewArBoard->Rows->Clear();

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand("SELECT * FROM ТаблоПрилета", sqlConnection);

		sqlConnection->Open();
		SqlDataReader^ reader = command->ExecuteReader();

		while (reader->Read())
		{
			dataGridViewArBoard->Rows->Add(
				reader["Id"]->ToString(),
				reader["НомерРейса"]->ToString(),
				reader["Время"]->ToString(),
				reader["Статус"]->ToString()
			);
		}

		reader->Close();
		sqlConnection->Close();
	}

	void ArrivalBoardForm::LoadWebBrowser()
	{
		this->webBrowser = gcnew System::Windows::Forms::WebBrowser();
		this->webBrowser->ScriptErrorsSuppressed = true;
		this->webBrowser->Location = System::Drawing::Point(20, this->dataGridViewArBoard->Bottom + 20);
		this->webBrowser->Size = System::Drawing::Size(this->ClientSize.Width - 2 * 20,  500);
		this->webBrowser->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right );
		this->Controls->Add(this->webBrowser);
		String^ mapHtml = "file:///C:/dev/Airport/Airport/vendor/map/map.html";
		this->webBrowser->Navigate(mapHtml);
	}

	void ArrivalBoardForm::dataGridViewDepBoard_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		if (this->dataGridViewArBoard->Columns[e->ColumnIndex]->Name == "Статус")
		{
			String^ newStatus = safe_cast<String^>(this->dataGridViewArBoard->Rows[e->RowIndex]->Cells["Статус"]->Value);
			String^ flightId = safe_cast<String^>(this->dataGridViewArBoard->Rows[e->RowIndex]->Cells["Id"]->Value);

			UpdateFlightStatusInDatabase(flightId, newStatus);
		}
	}

	void ArrivalBoardForm::UpdateFlightStatusInDatabase(String^ flightId, String^ newStatus)
	{
		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		SqlConnection^ sqlConnection = gcnew SqlConnection(connectionString);

		try
		{
			sqlConnection->Open();
			String^ query = "UPDATE ТаблоПрилета SET Статус = @newStatus WHERE Id = @flightId";
			SqlCommand^ command = gcnew SqlCommand(query, sqlConnection);
			command->Parameters->AddWithValue("@newStatus", newStatus);
			command->Parameters->AddWithValue("@flightId", flightId);

			command->ExecuteNonQuery();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Ошибка обновления статуса: " + ex->Message);
		}
		finally
		{
			sqlConnection->Close();
		}
	}
}