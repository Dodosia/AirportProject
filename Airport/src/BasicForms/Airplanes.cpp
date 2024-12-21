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
		this->dataGridViewAirplanes->Columns->Add("������", "������");
		this->dataGridViewAirplanes->Columns->Add("�����������", "�����������");
		this->dataGridViewAirplanes->Columns->Add("���������", "��� ������");
		this->dataGridViewAirplanes->Columns->Add("���������������������", "��� ����� � ������������");
		this->dataGridViewAirplanes->Columns->Add("������", "������");
		this->dataGridViewAirplanes->Columns->Add("��������������������������", "���� ���������� ������������");
		this->dataGridViewAirplanes->CellDoubleClick += gcnew DataGridViewCellEventHandler(this, &AirplanesForm::dataGridViewAirplanes_CellDoubleClick);

		this->Controls->Add(this->dataGridViewAirplanes);

		this->txtModel = gcnew MaterialSingleLineTextField();
		this->txtModel->Hint = "Id ��������";
		this->txtModel->ForeColor = System::Drawing::Color::Black;
		this->txtModel->Location = System::Drawing::Point(20, 20);
		this->txtModel->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtModel);

		this->txtYear = gcnew MaterialSingleLineTextField();
		this->txtYear->Hint = "������";
		this->txtYear->ForeColor = System::Drawing::Color::Black;
		this->txtYear->Location = System::Drawing::Point(370, 20);
		this->txtYear->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtYear);

		this->btnSearch = gcnew MaterialFlatButton();
		this->btnSearch->Text = "�����";
		this->btnSearch->Location = System::Drawing::Point(720, 15);
		this->btnSearch->Click += gcnew System::EventHandler(this, &AirplanesForm::btnSearch_Click);
		this->Controls->Add(this->btnSearch);

		this->btnClear = gcnew MaterialFlatButton();
		this->btnClear->Text = "��������";
		this->btnClear->Location = System::Drawing::Point(btnSearch->Right + 20, 15);
		this->btnClear->Click += gcnew System::EventHandler(this, &AirplanesForm::btnClear_Click);
		this->Controls->Add(this->btnClear);
    }

    void AirplanesForm::LoadAirplanes()
    {
		dataGridViewAirplanes->Rows->Clear();

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand("SELECT * FROM �������", sqlConnection);

		sqlConnection->Open();
		SqlDataReader^ reader = command->ExecuteReader();

		while (reader->Read())
		{
			int index = dataGridViewAirplanes->Rows->Add(
				reader["Id"]->ToString(),
				reader["������"]->ToString(),
				reader["�����������"]->ToString(),
				reader["���������"]->ToString(),
				reader["���������������������"]->ToString(),
				reader["������"]->ToString(),
				reader["��������������������������"]->ToString()
			);

			DataGridViewRow^ row = dataGridViewAirplanes->Rows[index];
			String^ status = row->Cells["������"]->Value->ToString();

			if (status == "����� � �����")
			{
				row->DefaultCellStyle->ForeColor = System::Drawing::Color::Green;
			}
			else if (status == "��������� ������")
			{
				row->DefaultCellStyle->ForeColor = System::Drawing::Color::Goldenrod;
			}
			else if (status == "�� �������")
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
			String^ model = row->Cells["������"]->Value->ToString();
			String^ capacity = row->Cells["�����������"]->Value->ToString();
			String^ baggageWeight = row->Cells["���������"]->Value->ToString();
			String^ year = row->Cells["���������������������"]->Value->ToString();
			String^ status = row->Cells["������"]->Value->ToString();
			String^ lastServiceDate = row->Cells["��������������������������"]->Value->ToString();
			AirplaneForm^ airplaneForm = gcnew AirplaneForm(airplaneId, model, capacity, baggageWeight, year, status, lastServiceDate);
			airplaneForm->ShowDialog();
		}
	}

	void AirplanesForm::btnSearch_Click(System::Object^ sender, System::EventArgs^ e)
	{
		String^ airplaneId = txtModel->Text; // ���������� txtModel ��� ����� Id ��������
		String^ status = txtYear->Text;

		String^ query = "SELECT * FROM ������� WHERE 1=1";

		if (!String::IsNullOrEmpty(airplaneId))
		{
			query += " AND Id = @id"; // ����� �� Id ��������
		}

		if (!String::IsNullOrEmpty(status))
		{
			query += " AND ������ = @status";
		}

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand(query, sqlConnection);

		if (!String::IsNullOrEmpty(airplaneId))
		{
			command->Parameters->AddWithValue("@id", airplaneId); // �������� ��� Id
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
				reader["������"]->ToString(),
				reader["�����������"]->ToString(),
				reader["���������"]->ToString(),
				reader["���������������������"]->ToString(),
				reader["������"]->ToString(),
				reader["��������������������������"]->ToString()
			);
			found = true;
		}

		reader->Close();
		sqlConnection->Close();

		if (!found)
		{
			LoadAirplanes();
			MessageBox::Show("������� � ��������� Id ��� �������� �� ������.", "����� �� ��� �����������", MessageBoxButtons::OK, MessageBoxIcon::Information);
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
			MessageBox::Show("������ ��� ���������� ������� ���������: " + ex->Message, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		finally
		{
			sqlConnection->Close();
		}
	}
}
