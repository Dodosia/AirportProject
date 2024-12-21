#include "Airplanes.h"

namespace Airport
{
    AirplanesForm::AirplanesForm()
    {
        InitializeComponent();
        LoadAirplanes();

		updateTimer = gcnew System::Windows::Forms::Timer();
		updateTimer->Interval = 60000;
		updateTimer->Tick += gcnew EventHandler(this, &AirplanesForm::UpdateTablo);
		updateTimer->Start();
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
		this->dataGridViewAirplanes->Columns->Add("Статус", "Статус");
		this->dataGridViewAirplanes->Columns->Add("ДатаПоследнегоОбслуживания", "Дата последнего обслуживания");
		this->dataGridViewAirplanes->CellDoubleClick += gcnew DataGridViewCellEventHandler(this, &AirplanesForm::dataGridViewAirplanes_CellDoubleClick);

		this->Controls->Add(this->dataGridViewAirplanes);

		this->txtModel = gcnew MaterialSingleLineTextField();
		this->txtModel->Hint = "Id самолета";
		this->txtModel->ForeColor = System::Drawing::Color::Black;
		this->txtModel->Location = System::Drawing::Point(20, 20);
		this->txtModel->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtModel);

		this->txtYear = gcnew MaterialSingleLineTextField();
		this->txtYear->Hint = "Статус";
		this->txtYear->ForeColor = System::Drawing::Color::Black;
		this->txtYear->Location = System::Drawing::Point(370, 20);
		this->txtYear->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtYear);

		this->btnSearch = gcnew MaterialFlatButton();
		this->btnSearch->Text = "Найти";
		this->btnSearch->Location = System::Drawing::Point(720, 15);
		this->btnSearch->Click += gcnew System::EventHandler(this, &AirplanesForm::btnSearch_Click);
		this->Controls->Add(this->btnSearch);

		this->btnClear = gcnew MaterialFlatButton();
		this->btnClear->Text = "Очистить";
		this->btnClear->Location = System::Drawing::Point(btnSearch->Right + 20, 15);
		this->btnClear->Click += gcnew System::EventHandler(this, &AirplanesForm::btnClear_Click);
		this->Controls->Add(this->btnClear);
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
			int index = dataGridViewAirplanes->Rows->Add(
				reader["Id"]->ToString(),
				reader["Модель"]->ToString(),
				reader["Вместимость"]->ToString(),
				reader["ВесБагажа"]->ToString(),
				reader["ГодВводаВЭксплуатацию"]->ToString(),
				reader["Статус"]->ToString(),
				reader["ДатаПоследнегоОбслуживания"]->ToString()
			);

			DataGridViewRow^ row = dataGridViewAirplanes->Rows[index];
			String^ status = row->Cells["Статус"]->Value->ToString();

			if (status == "Готов к полёту")
			{
				row->DefaultCellStyle->ForeColor = System::Drawing::Color::Green;
			}
			else if (status == "Требуется осмотр")
			{
				row->DefaultCellStyle->ForeColor = System::Drawing::Color::Goldenrod;
			}
			else if (status == "На ремонте")
			{
				row->DefaultCellStyle->ForeColor = System::Drawing::Color::Red;
			}
		}

		reader->Close();
		sqlConnection->Close();
    }

	void AirplanesForm::dataGridViewAirplanes_CellDoubleClick(Object^ sender, DataGridViewCellEventArgs^ e)
	{
		if (e->RowIndex >= 0)
		{
			DataGridViewRow^ row = this->dataGridViewAirplanes->Rows[e->RowIndex];

			String^ airplaneId = row->Cells["Id"]->Value->ToString();
			String^ model = row->Cells["Модель"]->Value->ToString();
			String^ capacity = row->Cells["Вместимость"]->Value->ToString();
			String^ baggageWeight = row->Cells["ВесБагажа"]->Value->ToString();
			String^ year = row->Cells["ГодВводаВЭксплуатацию"]->Value->ToString();
			String^ status = row->Cells["Статус"]->Value->ToString();
			String^ lastServiceDate = row->Cells["ДатаПоследнегоОбслуживания"]->Value->ToString();
			AirplaneForm^ airplaneForm = gcnew AirplaneForm(airplaneId, model, capacity, baggageWeight, year, status, lastServiceDate);
			airplaneForm->ShowDialog();
		}
	}

	void AirplanesForm::btnSearch_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ airplaneId = txtModel->Text; // Используем txtModel для ввода Id самолета
		String^ status = txtYear->Text;

		String^ query = "SELECT * FROM Самолет WHERE 1=1";

		if (!String::IsNullOrEmpty(airplaneId))
		{
			query += " AND Id = @id"; // Поиск по Id самолета
		}

		if (!String::IsNullOrEmpty(status))
		{
			query += " AND Статус = @status";
		}

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand(query, sqlConnection);

		if (!String::IsNullOrEmpty(airplaneId))
		{
			command->Parameters->AddWithValue("@id", airplaneId); // Параметр для Id
		}

		if (!String::IsNullOrEmpty(status))
		{
			command->Parameters->AddWithValue("@status", status);
		}

		sqlConnection->Open();
		SqlDataReader^ reader = command->ExecuteReader();
		dataGridViewAirplanes->Rows->Clear();

		bool found = false;

		while (reader->Read())
		{
			dataGridViewAirplanes->Rows->Add(
				reader["Id"]->ToString(),
				reader["Модель"]->ToString(),
				reader["Вместимость"]->ToString(),
				reader["ВесБагажа"]->ToString(),
				reader["ГодВводаВЭксплуатацию"]->ToString(),
				reader["Статус"]->ToString(),
				reader["ДатаПоследнегоОбслуживания"]->ToString()
			);
			found = true;
		}

		reader->Close();
		sqlConnection->Close();

		if (!found)
		{
			LoadAirplanes();
			MessageBox::Show("Самолет с указанным Id или статусом не найден.", "Поиск не дал результатов", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}

	void AirplanesForm::btnClear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		txtModel->Clear();
		txtYear->Clear();

		LoadAirplanes();
	}

	void AirplanesForm::UpdateTablo(System::Object^ sender, System::EventArgs^ e)
	{
		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);

		try
		{
			sqlConnection->Open();

			SqlCommand^ command = gcnew SqlCommand("EXEC dbo.UpdateAircraftStatusForInspection", sqlConnection);
			command->ExecuteNonQuery();

			LoadAirplanes();
		}
		catch (Exception^ ex)
		{
			MessageBox::Show("Ошибка при обновлении статуса самолетов: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally
		{
			sqlConnection->Close();
		}
	}
}
