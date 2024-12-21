#include "ArrivalBoard.h"

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
					"Выбранное время не может быть раньше времени прибытия!",
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

	ArrivalBoardForm::ArrivalBoardForm()
	{
		InitializeComponent();
		LoadFlights();

		updateTimer = gcnew System::Windows::Forms::Timer();
		updateTimer->Interval = 60000;
		updateTimer->Tick += gcnew EventHandler(this, &ArrivalBoardForm::UpdateTablo);
		updateTimer->Start();
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
		this->dataGridViewArBoard->CellBeginEdit += gcnew DataGridViewCellCancelEventHandler(this, &ArrivalBoardForm::dataGridViewDepBoard_CellBeginEdit);
		this->dataGridViewArBoard->CellFormatting += gcnew DataGridViewCellFormattingEventHandler(this, &ArrivalBoardForm::dataGridViewDepBoard_CellFormatting);
		this->dataGridViewArBoard->Columns->Add("Id", "Id");
		this->dataGridViewArBoard->Columns->Add("НомерРейса", "Номер рейса");
		this->dataGridViewArBoard->Columns->Add("Время", "Время прибытия");

		DataGridViewComboBoxColumn^ comboBoxColumn = gcnew DataGridViewComboBoxColumn();
		comboBoxColumn->Name = "Статус";
		comboBoxColumn->HeaderText = "Статус";
		comboBoxColumn->DataSource = gcnew array<String^> { "Отменен", "Задержан", "Ожидается", "Прилетел" };
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
		this->btnSearch->Click += gcnew System::EventHandler(this, &ArrivalBoardForm::btnSearch_Click);
		this->Controls->Add(this->btnSearch);

		this->btnClear = gcnew MaterialFlatButton();
		this->btnClear->Text = "Очистить";
		this->btnClear->Location = System::Drawing::Point(btnSearch->Right + 20, 15);
		this->btnClear->Click += gcnew System::EventHandler(this, &ArrivalBoardForm::btnClear_Click);
		this->Controls->Add(this->btnClear);

		LoadWebBrowser();
	}

	void ArrivalBoardForm::LoadFlights()
	{
		dataGridViewArBoard->Rows->Clear();

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand("UpdateTabloArrival", sqlConnection);

		sqlConnection->Open();
		SqlDataReader^ reader = command->ExecuteReader();

		if (!reader->HasRows)
		{
			MessageBox::Show("Нет данных для отображения");
		}

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

			if (newStatus == "Задержан")
			{
				String^ currentTime = safe_cast<String^>(this->dataGridViewArBoard->Rows[e->RowIndex]->Cells["Время"]->Value);
				DelayTimeForm^ delayForm = gcnew DelayTimeForm(currentTime);
				if (delayForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{
					String^ newTime = delayForm->SelectedTime;
					UpdateFlightStatusAndTimeInDatabase(flightId, newStatus, newTime);
					this->dataGridViewArBoard->Rows[e->RowIndex]->Cells
						["Время"]->Value = newTime;
				}
				else
				{
					this->dataGridViewArBoard->Rows[e->RowIndex]->Cells["Статус"]->Value = previousStatus;
				}
			}
			else
			{
				UpdateFlightStatusInDatabase(flightId, newStatus);
			}
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

	void ArrivalBoardForm::UpdateTablo(System::Object^ sender, System::EventArgs^ e)
	{
		LoadFlights();
	}

	void ArrivalBoardForm::btnSearch_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ searchFlightNumber = txtFlight->Text->Trim();

		bool found = false;

		for each (DataGridViewRow ^ row in dataGridViewArBoard->Rows)
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
			for each (DataGridViewRow ^ row in dataGridViewArBoard->Rows)
			{
				row->Visible = true;
			}
			MessageBox::Show("Рейс не найден.", "Поиск не дал результатов", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}

	void ArrivalBoardForm::btnClear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		txtFlight->Clear(); 

		for each (DataGridViewRow ^ row in dataGridViewArBoard->Rows)
		{
			row->Visible = true;
		}
	}
	void ArrivalBoardForm::dataGridViewDepBoard_CellBeginEdit(Object^ sender, DataGridViewCellCancelEventArgs^ e)
	{
		if (this->dataGridViewArBoard->Columns[e->ColumnIndex]->Name == "Статус")
		{
			previousStatus = Convert::ToString(this->dataGridViewArBoard->Rows[e->RowIndex]->Cells[e->ColumnIndex]->Value);

			if (previousStatus == "Прилетел")
			{
				MessageBox::Show("Статус прибывшего рейса нельзя изменить.", "Предупреждение", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				e->Cancel = true;
			}
		}
	}

	void ArrivalBoardForm::UpdateFlightStatusAndTimeInDatabase(String^ flightId, String^ newStatus, String^ newTime)
	{
		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		SqlConnection^ sqlConnection = gcnew SqlConnection(connectionString);

		try
		{
			sqlConnection->Open();
			String^ query = "UPDATE ТаблоПрилета SET Статус = @newStatus, Время = @newTime WHERE Id = @flightId";
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

	void ArrivalBoardForm::dataGridViewDepBoard_CellFormatting(System::Object^ sender, System::Windows::Forms::DataGridViewCellFormattingEventArgs^ e)
	{
		DataGridViewRow^ row = this->dataGridViewArBoard->Rows[e->RowIndex];

		String^ status = safe_cast<String^>(row->Cells["Статус"]->Value);

		if (status != nullptr)
		{
			if (status == "Задержан")
			{
				if (this->dataGridViewArBoard->Columns[e->ColumnIndex]->Name == "Время")
				{
					e->CellStyle->ForeColor = System::Drawing::Color::Red;
				}
			}
			else if (status == "Отменен")
			{
				if (this->dataGridViewArBoard->Columns[e->ColumnIndex]->Name != "Статус")
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
}