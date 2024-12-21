#include "TechFlightsForm.h"

namespace Airport
{
    TechFlight::TechFlight()
    {
        InitializeComponent();
        LoadFlights();
    }

    TechFlight::~TechFlight()
    {
        if (components)
        {
            delete components;
        }
    }

    void TechFlight::InitializeComponent()
    {
        this->components = gcnew System::ComponentModel::Container();
        this->BackColor = System::Drawing::Color::White;
        int rightMargin = 20;
        int bottomMargin = 20;
        this->dataGridViewFlights = gcnew DataGridView();
        this->dataGridViewFlights->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
        this->dataGridViewFlights->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
        this->dataGridViewFlights->DefaultCellStyle->BackColor = System::Drawing::Color::White;
        this->dataGridViewFlights->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
        this->dataGridViewFlights->ColumnHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->dataGridViewFlights->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::White;
        this->dataGridViewFlights->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
        this->dataGridViewFlights->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
        this->dataGridViewFlights->EnableHeadersVisualStyles = false;
        this->dataGridViewFlights->GridColor = System::Drawing::Color::LightGray;
        this->dataGridViewFlights->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
        this->dataGridViewFlights->RowHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->dataGridViewFlights->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
        this->dataGridViewFlights->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
        this->dataGridViewFlights->Dock = System::Windows::Forms::DockStyle::Fill;
        this->dataGridViewFlights->Margin = System::Windows::Forms::Padding(10);
        this->dataGridViewFlights->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
        this->dataGridViewFlights->BackgroundColor = System::Drawing::Color::White;
        this->dataGridViewFlights->ForeColor = System::Drawing::Color::Black;
        this->dataGridViewFlights->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
        this->dataGridViewFlights->Location = System::Drawing::Point(20, 80);
        this->dataGridViewFlights->Size = System::Drawing::Size(this->ClientSize.Width - this->dataGridViewFlights->Location.X - rightMargin, this->ClientSize.Height - this->dataGridViewFlights->Location.Y - bottomMargin);
        this->dataGridViewFlights->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
  
        DataGridViewComboBoxColumn^ airplaneColumn = gcnew DataGridViewComboBoxColumn();
        airplaneColumn->Name = "Id��������";
        airplaneColumn->HeaderText = "Id ��������";
        airplaneColumn->DisplayStyle = DataGridViewComboBoxDisplayStyle::DropDownButton;
        airplaneColumn->ReadOnly = false;
        airplaneColumn->DataSource = GetAvailableAirplanes();
        airplaneColumn->ValueMember = "Id";
        airplaneColumn->DisplayMember = "Id";

        this->dataGridViewFlights->Columns->Add("�����", "�����");
        this->dataGridViewFlights->Columns->Add(airplaneColumn);
        this->dataGridViewFlights->Columns->Add("��������������", "�������� ������");
        this->dataGridViewFlights->Columns->Add("���������������", "�������� �������");
        this->dataGridViewFlights->Columns->Add("����������������", "����� �����������");
        this->dataGridViewFlights->Columns->Add("�������������", "����� ��������");
        this->dataGridViewFlights->Columns->Add("����������", "����� � ����");

        this->dataGridViewFlights->Columns["�����"]->ReadOnly = true;
        this->dataGridViewFlights->Columns["��������������"]->ReadOnly = true;
        this->dataGridViewFlights->Columns["���������������"]->ReadOnly = true;
        this->dataGridViewFlights->Columns["����������������"]->ReadOnly = true;
        this->dataGridViewFlights->Columns["�������������"]->ReadOnly = true;
        this->dataGridViewFlights->Columns["����������"]->ReadOnly = true;

        this->dataGridViewFlights->CellBeginEdit += gcnew System::Windows::Forms::DataGridViewCellCancelEventHandler(this, &TechFlight::dataGridViewFlights_CellBeginEdit);
        this->dataGridViewFlights->CellEndEdit += gcnew DataGridViewCellEventHandler(this, &TechFlight::dataGridViewFlights_CellEndEdit);

        this->Controls->Add(this->dataGridViewFlights);

        this->txtNumber = gcnew MaterialSingleLineTextField();
        this->txtNumber->Hint = "����� �����";
        this->txtNumber->BackColor = System::Drawing::Color::Blue;
        this->txtNumber->ForeColor = System::Drawing::Color::Black;
        this->txtNumber->Location = System::Drawing::Point(350, 20);
        this->txtNumber->Size = System::Drawing::Size(300, 20);
        this->Controls->Add(this->txtNumber);

        this->txtAirport = gcnew MaterialSingleLineTextField();
        this->txtAirport->Hint = "��� ��������";
        this->txtAirport->BackColor = System::Drawing::Color::Blue;
        this->txtAirport->ForeColor = System::Drawing::Color::Black;
        this->txtAirport->Location = System::Drawing::Point(20, 20);
        this->txtAirport->Size = System::Drawing::Size(300, 20);
        this->Controls->Add(this->txtAirport);

        this->btnSearch = gcnew MaterialFlatButton();
        this->btnSearch->Text = "�����";
        this->btnSearch->Location = System::Drawing::Point(700, 15);
        this->btnSearch->Click += gcnew System::EventHandler(this, &TechFlight::btnSearch_Click);
        this->Controls->Add(this->btnSearch);

        this->btnClear = gcnew MaterialFlatButton();
        this->btnClear->Text = "��������";
        this->btnClear->Location = System::Drawing::Point(btnSearch->Right + 20, 15);
        this->btnClear->Click += gcnew System::EventHandler(this, &TechFlight::btnClear_Click);
        this->Controls->Add(this->btnClear);
    }


    void TechFlight::LoadFlights()
    {
        dataGridViewFlights->Rows->Clear();

        String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
        sqlConnection = gcnew SqlConnection(connectionString);
        SqlCommand^ command = gcnew SqlCommand("SELECT * FROM ����", sqlConnection);

        try
        {
            sqlConnection->Open();
            SqlDataReader^ reader = command->ExecuteReader();

            while (reader->Read())
            {
                dataGridViewFlights->Rows->Add(
                    reader["�����"]->ToString(),
                    reader["Id��������"]->ToString(),
                    reader["��������������"]->ToString(),
                    reader["���������������"]->ToString(),
                    reader["����������������"]->ToString(),
                    reader["�������������"]->ToString(),
                    reader["����������"]->ToString()
                );
            }

            reader->Close();
        }
        catch (Exception^ ex)
        {
            MessageBox::Show("������ ��� �������� ������: " + ex->Message);
        }
        finally
        {
            sqlConnection->Close();
        }
    }

    void TechFlight::btnSearch_Click(System::Object^ sender, System::EventArgs^ e)
    {
        String^ number = this->txtNumber->Text;
        String^ airplaneId = this->txtAirport->Text;

        dataGridViewFlights->Rows->Clear();

        if (String::IsNullOrEmpty(number) && String::IsNullOrEmpty(airplaneId)) {
            LoadFlights();
            return;
        }

        String^ query = "SELECT * FROM ���� WHERE 1=1";

        if (!String::IsNullOrEmpty(number))
        {
            query += " AND ����� LIKE @Number";
        }
        if (!String::IsNullOrEmpty(airplaneId))
        {
            query += " AND Id�������� LIKE @AirplaneId";
        }

        SqlConnection^ sqlConnection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");
        SqlCommand^ command = gcnew SqlCommand(query, sqlConnection);

        if (!String::IsNullOrEmpty(number))
        {
            command->Parameters->AddWithValue("@Number", "%" + number + "%");
        }
        if (!String::IsNullOrEmpty(airplaneId)) 
        {
            command->Parameters->AddWithValue("@AirplaneId", "%" + airplaneId + "%");
        }

        sqlConnection->Open();
        SqlDataReader^ reader = command->ExecuteReader();

        bool found = false;

        while (reader->Read())
        {
            dataGridViewFlights->Rows->Add(
                reader["�����"]->ToString(),
                reader["Id��������"]->ToString(),
                reader["��������������"]->ToString(),
                reader["���������������"]->ToString(),
                reader["����������������"]->ToString(),
                reader["�������������"]->ToString(),
                reader["����������"]->ToString()
            );
            found = true;
        }

        reader->Close();
        sqlConnection->Close();

        if (!found)
        {
            LoadFlights();
            MessageBox::Show("���� ��� ������� � �������� Id �� ������.", "����� �� ��� �����������", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
    }

    void TechFlight::btnClear_Click(System::Object^ sender, System::EventArgs^ e)
    {
        this->txtNumber->Text = "";
        this->txtAirport->Text = "";

        dataGridViewFlights->Rows->Clear();

        LoadFlights();
    }

    void TechFlight::dataGridViewFlights_CellEndEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
    {
        if (e->ColumnIndex == dataGridViewFlights->Columns["Id��������"]->Index)
        {
            String^ flightNumber = dataGridViewFlights->Rows[e->RowIndex]->Cells["�����"]->Value->ToString();
            String^ newAirplaneId = dataGridViewFlights->Rows[e->RowIndex]->Cells["Id��������"]->Value->ToString();

            SqlConnection^ sqlConnection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");
            SqlCommand^ command = gcnew SqlCommand("UpdateAirplaneId", sqlConnection);
            command->CommandType = CommandType::StoredProcedure;

            command->Parameters->AddWithValue("@FlightId", flightNumber);
            command->Parameters->AddWithValue("@NewAirplaneId", newAirplaneId);

            try
            {
                sqlConnection->Open();
                command->ExecuteNonQuery();
                MessageBox::Show("Id �������� ������� ��������.", "�����", MessageBoxButtons::OK, MessageBoxIcon::Information);

                dataGridViewFlights->Rows[e->RowIndex]->Cells["Id��������"]->Tag = newAirplaneId;

                dataGridViewFlights->Rows[e->RowIndex]->Cells["Id��������"]->Value = newAirplaneId;
            }
            catch (SqlException^ ex)
            {
                MessageBox::Show("������ ��� ���������� Id��������: " + ex->Message, "������", MessageBoxButtons::OK, MessageBoxIcon::Error);

                dataGridViewFlights->Rows[e->RowIndex]->Cells["Id��������"]->Value = originalAirplaneId;
            }

            finally
            {
                sqlConnection->Close();
            }
        }
    }

    void TechFlight::dataGridViewFlights_CellBeginEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellCancelEventArgs^ e)
    {
        if (e->ColumnIndex == dataGridViewFlights->Columns["Id��������"]->Index)
        {
            originalAirplaneId = dataGridViewFlights->Rows[e->RowIndex]->Cells["Id��������"]->Value->ToString();

            dataGridViewFlights->Rows[e->RowIndex]->Cells["Id��������"]->Tag = originalAirplaneId;
        }
    }

    String^ TechFlight::GetAirplaneStatusById(String^ airplaneId)
    {
        int id = Int32::Parse(airplaneId);

        String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";

        SqlConnection^ sqlConnection = gcnew SqlConnection(connectionString);

        SqlCommand^ command = gcnew SqlCommand("GetAirplaneStatus", sqlConnection);
        command->CommandType = CommandType::StoredProcedure;

        command->Parameters->AddWithValue("@AirplaneId", id);

        String^ status;

        sqlConnection->Open();

        SqlDataReader^ reader = command->ExecuteReader();

        if (reader->Read())
        {
            status = reader["������"]->ToString();
        }
        else
        {
            status = "������ �� ������"; 
        }

        reader->Close();

        return status;
    }

    System::Data::DataTable^ TechFlight::GetAvailableAirplanes()
    {
        System::Data::DataTable^ availableAirplanes = gcnew System::Data::DataTable();
        availableAirplanes->Columns->Add("Id");
        availableAirplanes->Columns->Add("������"); 

        String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
        SqlConnection^ sqlConnection = gcnew SqlConnection(connectionString);
        SqlCommand^ command = gcnew SqlCommand("SELECT Id, ������ FROM �������", sqlConnection);

        try
        {
            sqlConnection->Open();
            SqlDataReader^ reader = command->ExecuteReader();

            while (reader->Read())
            {
                System::Data::DataRow^ row = availableAirplanes->NewRow();
                row["Id"] = reader["Id"];
                row["������"] = reader["������"]; 
                availableAirplanes->Rows->Add(row);
            }

            reader->Close();
        }
        catch (Exception^ ex)
        {
            MessageBox::Show("������ ��� �������� ��������� ���������: " + ex->Message);
        }
        finally
        {
            sqlConnection->Close();
        }

        return availableAirplanes;
    }
}
