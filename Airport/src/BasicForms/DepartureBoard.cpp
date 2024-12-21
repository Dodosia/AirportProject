#include "DepartureBoard.h"

namespace Airport
{
	public ref class DelayTimeForm : public System::Windows::Forms::Form
	{
	public:
		property String^ SelectedTime;

		DelayTimeForm(String^ currentTime)
		{
			InitializeComponent();

			DateTime defaultTime;
			if (DateTime::TryParse(currentTime, defaultTime))
			{
				this->dateTimePicker->Value = defaultTime;
			}

			DateTime minTime;
			if (DateTime::TryParse(currentTime, minTime))
			{
				this->dateTimePicker->MinDate = minTime;
			}
		}

	private:
		void InitializeComponent()
		{
			System::Drawing::Icon^ icon = gcnew System::Drawing::Icon("main_logo.ico");
			this->Icon = icon;
			this->Text = "Изменить время";
			this->Size = System::Drawing::Size(100, 50);
			this->StartPosition = FormStartPosition::CenterScreen;

			this->Width = 300;
			this->Height = 150;

			this->dateTimePicker = gcnew System::Windows::Forms::DateTimePicker();
			this->dateTimePicker->Format = System::Windows::Forms::DateTimePickerFormat::Time;
			this->dateTimePicker->ShowUpDown = true;
			this->dateTimePicker->Size = System::Drawing::Size(160, 40);
			this->dateTimePicker->Font = gcnew System::Drawing::Font(L"Segoe UI", 14); // Увеличенный шрифт
			this->dateTimePicker->Location = System::Drawing::Point(
				(this->ClientSize.Width - this->dateTimePicker->Width) / 2,  // Центр по ширине
				20                                                          // Отступ сверху
			);

			this->btnOK = gcnew System::Windows::Forms::Button();
			this->btnOK->Text = "OK";
			this->btnOK->Size = System::Drawing::Size(80, 30);
			this->btnOK->Location = System::Drawing::Point(
				(this->ClientSize.Width - this->btnOK->Width) / 2,  // Центр по ширине
				this->dateTimePicker->Bottom + 20                  // Отступ под DateTimePicker
			);
			this->btnOK->Click += gcnew System::EventHandler(this, &DelayTimeForm::btnOK_Click);

			this->Controls->Add(this->dateTimePicker);
			this->Controls->Add(this->btnOK);
		}

		void btnOK_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (this->dateTimePicker->Value < this->dateTimePicker->MinDate)
			{
				MessageBox::Show(
					"Выбранное время не может быть раньше времени отправления!",
					"Ошибка",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error
				);
				return;
			}

			this->SelectedTime = this->dateTimePicker->Value.ToShortTimeString();
			this->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->Close();
		}

		System::Windows::Forms::DateTimePicker^ dateTimePicker;
		System::Windows::Forms::Button^ btnOK;
	};

    DepartureBoardForm::DepartureBoardForm()
    {
        InitializeComponent();
        LoadFlights();

		updateTimer = gcnew System::Windows::Forms::Timer();
		updateTimer->Interval = 60000;
		updateTimer->Tick += gcnew EventHandler(this, &DepartureBoardForm::UpdateTablo);
		updateTimer->Start();
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
		this->dataGridViewDepBoard->CellBeginEdit += gcnew DataGridViewCellCancelEventHandler(this, &DepartureBoardForm::dataGridViewDepBoard_CellBeginEdit);
		this->dataGridViewDepBoard->RowTemplate->Height = 40;
		this->dataGridViewDepBoard->Columns->Add("Id", "Id");
		this->dataGridViewDepBoard->Columns->Add("НомерРейса", "Номер рейса");
		this->dataGridViewDepBoard->Columns->Add("Время", "Время отправления");

		DataGridViewComboBoxColumn^ comboBoxColumn = gcnew DataGridViewComboBoxColumn();
		comboBoxColumn->Name = "Статус";
		comboBoxColumn->HeaderText = "Статус";
		comboBoxColumn->DataSource = gcnew array<String^> { "Отменен", "Задержан", "Вылетел", "Идет регистрация", "Идет посадка", "Планируется" };
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
		this->btnSearch->Click += gcnew System::EventHandler(this, &DepartureBoardForm::btnSearch_Click);
		this->Controls->Add(this->btnSearch);

		this->btnClear = gcnew MaterialFlatButton();
		this->btnClear->Text = "Очистить";
		this->btnClear->Location = System::Drawing::Point(btnSearch->Right + 20, 15);
		this->btnClear->Click += gcnew System::EventHandler(this, &DepartureBoardForm::btnClear_Click);
		this->Controls->Add(this->btnClear);

		LoadWebBrowser();
    }

    void DepartureBoardForm::LoadFlights()
    {
		try
		{
			dataGridViewDepBoard->Rows->Clear();

			String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
			sqlConnection = gcnew SqlConnection(connectionString);
			SqlCommand^ command = gcnew SqlCommand("UpdateTabloDeparture", sqlConnection);

			sqlConnection->Open();
			SqlDataReader^ reader = command->ExecuteReader();

			if (!reader->HasRows)
			{
				MessageBox::Show("Нет данных для отображения");
			}

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
		}
		catch (Exception^ e)
		{
			MessageBox::Show("Ошибка: " + e->Message);
		}
		finally
		{
			sqlConnection->Close();
		}
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
		DataGridViewRow^ row = this->dataGridViewDepBoard->Rows[e->RowIndex];

		String^ status = safe_cast<String^>(row->Cells["Статус"]->Value);

		if (status != nullptr)
		{
			if (status == "Задержан")
			{
				if (this->dataGridViewDepBoard->Columns[e->ColumnIndex]->Name == "Время")
				{
					e->CellStyle->ForeColor = System::Drawing::Color::Red;
				}
			}
			else if (status == "Отменен")
			{
				if (this->dataGridViewDepBoard->Columns[e->ColumnIndex]->Name != "Статус")
				{
					e->CellStyle->Font = gcnew System::Drawing::Font(e->CellStyle->Font,
						System::Drawing::FontStyle::Strikeout);
				}
			}
			else
			{
				e->CellStyle->Font = gcnew System::Drawing::Font(e->CellStyle->Font,
					System::Drawing::FontStyle::Regular);
			}
		}
	}

	void DepartureBoardForm::dataGridViewDepBoard_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		if (this->dataGridViewDepBoard->Columns[e->ColumnIndex]->Name == "Статус")
		{
			String^ newStatus = safe_cast<String^>(this->dataGridViewDepBoard->Rows[e->RowIndex]->Cells["Статус"]->Value);
			String^ flightId = safe_cast<String^>(this->dataGridViewDepBoard->Rows[e->RowIndex]->Cells["Id"]->Value);

			if (newStatus == "Задержан")
			{
				String^ currentTime = safe_cast<String^>(this->dataGridViewDepBoard->Rows[e->RowIndex]->Cells["Время"]->Value);
				DelayTimeForm^ delayForm = gcnew DelayTimeForm(currentTime);
				if (delayForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					String^ newTime = delayForm->SelectedTime;
					UpdateFlightStatusAndTimeInDatabase(flightId, newStatus, newTime);
					this->dataGridViewDepBoard->Rows[e->RowIndex]->Cells
						["Время"]->Value = newTime;
				}
				else
				{
					this->dataGridViewDepBoard->Rows[e->RowIndex]->Cells["Статус"]->Value = previousStatus;
				}
			}
			else
			{
				UpdateFlightStatusInDatabase(flightId, newStatus);
			}
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

	void DepartureBoardForm::UpdateFlightStatusAndTimeInDatabase(String^ flightId, String^ newStatus, String^ newTime)
	{
		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		SqlConnection^ sqlConnection = gcnew SqlConnection(connectionString);

		try
		{
			sqlConnection->Open();
			String^ query = "UPDATE ТаблоВылета SET Статус = @newStatus, Время = @newTime WHERE Id = @flightId";
			SqlCommand^ command = gcnew SqlCommand(query, sqlConnection);
			command->Parameters->AddWithValue("@newStatus", newStatus);
			command->Parameters->AddWithValue("@newTime", newTime);
			command->Parameters->AddWithValue("@flightId", flightId);

			command->ExecuteNonQuery();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Ошибка обновления данных: " + ex->Message);
		}
		finally
		{
			sqlConnection->Close();
		}
	}

	void DepartureBoardForm::UpdateTablo(System::Object^ sender, System::EventArgs^ e)
	{
		LoadFlights();
	}

	void DepartureBoardForm::btnSearch_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ searchFlightNumber = txtFlight->Text->Trim();

		bool found = false;

		for each (DataGridViewRow ^ row in dataGridViewDepBoard->Rows)
		{
			if (row->Cells["НомерРейса"]->Value != nullptr)
			{
				if (row->Cells["НомерРейса"]->Value->ToString()->Contains(searchFlightNumber))
				{
					row->Visible = true;
					found = true;
				}
				else
				{
					row->Visible = false;
				}
			}
		}
		if (!found)
		{
			for each (DataGridViewRow ^ row in dataGridViewDepBoard->Rows)
			{
				row->Visible = true;
			}
			MessageBox::Show("Рейс не найден.", "Поиск не дал результатов", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}

	void DepartureBoardForm::btnClear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		txtFlight->Clear();

		for each (DataGridViewRow ^ row in dataGridViewDepBoard->Rows)
		{
			row->Visible = true;
		}
	}

	void DepartureBoardForm::dataGridViewDepBoard_CellBeginEdit(Object^ sender, DataGridViewCellCancelEventArgs^ e)
	{
		if (this->dataGridViewDepBoard->Columns[e->ColumnIndex]->Name == "Статус")
		{
			previousStatus = Convert::ToString(this->dataGridViewDepBoard->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value);

			if (previousStatus == "Вылетел")
			{
				MessageBox::Show("Статус уже отправленного рейса нельзя изменить.", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				e->Cancel = true;
			}
		}
	}

	void DepartureBoardForm::UpdateFlightTimeInDatabase(String^ flightId, DateTime^ newTime)
	{
		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		SqlConnection^ sqlConnection = gcnew SqlConnection(connectionString);

		try
		{
			sqlConnection->Open();
			String^ query = "UPDATE ТаблоВылета SET ВремяОтправления = @newTime WHERE Id = @flightId";
			SqlCommand^ command = gcnew SqlCommand(query, sqlConnection);
			command->Parameters->AddWithValue("@newTime", newTime);
			command->Parameters->AddWithValue("@flightId", flightId);

			command->ExecuteNonQuery();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Ошибка обновления времени: " + ex->Message);
		}
		finally
		{
			sqlConnection->Close();
		}
	}

	void DepartureBoardForm::HighlightRowAsDelayed(int rowIndex)
	{
		DataGridViewRow^ row = dataGridViewDepBoard->Rows[rowIndex];
		row->DefaultCellStyle->BackColor = System::Drawing::Color::FromArgb(255, 220, 220);
	}
}
