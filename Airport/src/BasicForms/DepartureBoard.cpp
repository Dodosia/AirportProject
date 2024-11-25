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
		this->dataGridViewDepBoard->Margin = System::Windows::Forms::Padding(10);
		this->dataGridViewDepBoard->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
		this->dataGridViewDepBoard->BackgroundColor = System::Drawing::Color::White;
		this->dataGridViewDepBoard->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewDepBoard->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		this->dataGridViewDepBoard->Size = System::Drawing::Size(this->ClientSize.Width - 2 * rightMargin, 300);
		this->dataGridViewDepBoard->Location = System::Drawing::Point(rightMargin, 80);
		this->dataGridViewDepBoard->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);

		this->dataGridViewDepBoard->RowTemplate->Height = 40;
		this->dataGridViewDepBoard->Columns->Add("Id", "Id");
		this->dataGridViewDepBoard->Columns->Add("НомерРейса", "Номер рейса");
		this->dataGridViewDepBoard->Columns->Add("Время", "Время прибытия");

		DataGridViewComboBoxColumn^ comboBoxColumn = gcnew DataGridViewComboBoxColumn();
		comboBoxColumn->Name = "Статус";
		comboBoxColumn->HeaderText = "Статус";
		comboBoxColumn->DataSource = gcnew array<String^> { "Отменен", "Задержан", "Отправлен", "Регистрация" };
		this->dataGridViewDepBoard->Columns->Add(comboBoxColumn);

		this->dataGridViewDepBoard->CellEndEdit += gcnew DataGridViewCellEventHandler(this, &DepartureBoardForm::dataGridViewDepBoard_CellEndEdit);
		this->dataGridViewDepBoard->CellFormatting += gcnew DataGridViewCellFormattingEventHandler(this, &DepartureBoardForm::dataGridViewDepBoard_CellFormatting);

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

		LoadWebBrowser();
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

	void DepartureBoardForm::LoadWebBrowser()
	{
		this->webBrowser = gcnew System::Windows::Forms::WebBrowser();
		this->webBrowser->ScriptErrorsSuppressed = true;
		this->webBrowser->Location = System::Drawing::Point(20, this->dataGridViewDepBoard->Bottom + 20);
		this->webBrowser->Size = System::Drawing::Size(this->ClientSize.Width - 2 * 20, 500);
		this->webBrowser->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Left | AnchorStyles::Right);
		this->Controls->Add(this->webBrowser);
		String^ mapHtml = "file:///C:/dev/Airport/Airport/vendor/map/map.html";
		this->webBrowser->Navigate(mapHtml);
	}

	void DepartureBoardForm::dataGridViewDepBoard_CellFormatting(System::Object^ sender, System::Windows::Forms::DataGridViewCellFormattingEventArgs^ e)
	{
		if (this->dataGridViewDepBoard->Columns[e->ColumnIndex]->Name == "Статус")
		{
			DataGridViewComboBoxCell^ comboBoxCell = dynamic_cast<DataGridViewComboBoxCell^>(this->dataGridViewDepBoard->Rows[e->RowIndex]->Cells[e->ColumnIndex]);
			if (comboBoxCell != nullptr)
			{
				String^ status = safe_cast<String^>(e->Value);

				if (status == "Отменен")
				{
					e->CellStyle->BackColor = System::Drawing::Color::FromArgb(255, 220, 220); // Светло-красный
				}
				else if (status == "Задержан")
				{
					e->CellStyle->BackColor = System::Drawing::Color::FromArgb(255, 255, 230); // Светло-жёлтый
				}
				else if (status == "Отправлен")
				{
					e->CellStyle->BackColor = System::Drawing::Color::FromArgb(220, 255, 220); // Светло-зелёный
				}
				else if (status == "Регистрация")
				{
					e->CellStyle->BackColor = System::Drawing::Color::FromArgb(220, 230, 255); // Светло-синий
				}
				else
				{
					e->CellStyle->BackColor = System::Drawing::Color::White; // Цвет по умолчанию
				}
				e->CellStyle->ForeColor = System::Drawing::Color::Black;
			}
		}
	}

	void DepartureBoardForm::dataGridViewDepBoard_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		if (this->dataGridViewDepBoard->Columns[e->ColumnIndex]->Name == "Статус")
		{
			String^ newStatus = safe_cast<String^>(this->dataGridViewDepBoard->Rows[e->RowIndex]->Cells["Статус"]->Value);
			String^ flightId = safe_cast<String^>(this->dataGridViewDepBoard->Rows[e->RowIndex]->Cells["Id"]->Value);

			UpdateFlightStatusInDatabase(flightId, newStatus);
		}
	}

	void DepartureBoardForm::UpdateFlightStatusInDatabase(String^ flightId, String^ newStatus)
	{
		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		SqlConnection^ sqlConnection = gcnew SqlConnection(connectionString);

		try
		{
			sqlConnection->Open();
			String^ query = "UPDATE ТаблоВылета SET Статус = @newStatus WHERE Id = @flightId";
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
