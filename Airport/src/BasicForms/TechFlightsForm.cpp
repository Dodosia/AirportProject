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
        airplaneColumn->Name = "IdСамолета";
        airplaneColumn->HeaderText = "Id Самолета";
        airplaneColumn->DisplayStyle = DataGridViewComboBoxDisplayStyle::DropDownButton;
        airplaneColumn->ReadOnly = false;
        airplaneColumn->DataSource = GetAvailableAirplanes();
        airplaneColumn->ValueMember = "Id";
        airplaneColumn->DisplayMember = "Id";

        this->dataGridViewFlights->Columns->Add("Номер", "Номер");
        this->dataGridViewFlights->Columns->Add(airplaneColumn);
        this->dataGridViewFlights->Columns->Add("АэропортВылета", "Аэропорт вылета");
        this->dataGridViewFlights->Columns->Add("АэропортПрилета", "Аэропорт прилета");
        this->dataGridViewFlights->Columns->Add("ВремяОтправления", "Время отправления");
        this->dataGridViewFlights->Columns->Add("ВремяПрибытия", "Время прибытия");
        this->dataGridViewFlights->Columns->Add("ВремяВпути", "Время в пути");

        this->dataGridViewFlights->Columns["Номер"]->ReadOnly = true;
        this->dataGridViewFlights->Columns["АэропортВылета"]->ReadOnly = true;
        this->dataGridViewFlights->Columns["АэропортПрилета"]->ReadOnly = true;
        this->dataGridViewFlights->Columns["ВремяОтправления"]->ReadOnly = true;
        this->dataGridViewFlights->Columns["ВремяПрибытия"]->ReadOnly = true;
        this->dataGridViewFlights->Columns["ВремяВпути"]->ReadOnly = true;

        this->dataGridViewFlights->CellBeginEdit += gcnew System::Windows::Forms::DataGridViewCellCancelEventHandler(this, &TechFlight::dataGridViewFlights_CellBeginEdit);
        this->dataGridViewFlights->CellEndEdit += gcnew DataGridViewCellEventHandler(this, &TechFlight::dataGridViewFlights_CellEndEdit);

        this->Controls->Add(this->dataGridViewFlights);

        this->txtNumber = gcnew MaterialSingleLineTextField();
        this->txtNumber->Hint = "Номер рейса";
        this->txtNumber->BackColor = System::Drawing::Color::Blue;
        this->txtNumber->ForeColor = System::Drawing::Color::Black;
        this->txtNumber->Location = System::Drawing::Point(350, 20);
        this->txtNumber->Size = System::Drawing::Size(300, 20);
        this->Controls->Add(this->txtNumber);

        this->txtAirport = gcnew MaterialSingleLineTextField();
        this->txtAirport->Hint = "Код самолета";
        this->txtAirport->BackColor = System::Drawing::Color::Blue;
        this->txtAirport->ForeColor = System::Drawing::Color::Black;
        this->txtAirport->Location = System::Drawing::Point(20, 20);
        this->txtAirport->Size = System::Drawing::Size(300, 20);
        this->Controls->Add(this->txtAirport);

        this->btnSearch = gcnew MaterialFlatButton();
        this->btnSearch->Text = "Найти";
        this->btnSearch->Location = System::Drawing::Point(700, 15);
        this->btnSearch->Click += gcnew System::EventHandler(this, &TechFlight::btnSearch_Click);
        this->Controls->Add(this->btnSearch);

        this->btnClear = gcnew MaterialFlatButton();
        this->btnClear->Text = "Очистить";
        this->btnClear->Location = System::Drawing::Point(btnSearch->Right + 20, 15);
        this->btnClear->Click += gcnew System::EventHandler(this, &TechFlight::btnClear_Click);
        this->Controls->Add(this->btnClear);
    }


    void TechFlight::LoadFlights()
    {
        dataGridViewFlights->Rows->Clear();

        String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
        sqlConnection = gcnew SqlConnection(connectionString);
        SqlCommand^ command = gcnew SqlCommand("SELECT * FROM Рейс", sqlConnection);

        try
        {
            sqlConnection->Open();
            SqlDataReader^ reader = command->ExecuteReader();

            while (reader->Read())
            {
                dataGridViewFlights->Rows->Add(
                    reader["Номер"]->ToString(),
                    reader["IdСамолета"]->ToString(),
                    reader["АэропортВылета"]->ToString(),
                    reader["АэропортПрилета"]->ToString(),
                    reader["ВремяОтправления"]->ToString(),
                    reader["ВремяПрибытия"]->ToString(),
                    reader["ВремяВпути"]->ToString()
                );
            }

            reader->Close();
        }
        catch (Exception^ ex)
        {
            MessageBox::Show("Ошибка при загрузке рейсов: " + ex->Message);
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

        String^ query = "SELECT * FROM Рейс WHERE 1=1";

        if (!String::IsNullOrEmpty(number))
        {
            query += " AND Номер LIKE @Number";
        }
        if (!String::IsNullOrEmpty(airplaneId))
        {
            query += " AND IdСамолета LIKE @AirplaneId";
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
                reader["Номер"]->ToString(),
                reader["IdСамолета"]->ToString(),
                reader["АэропортВылета"]->ToString(),
                reader["АэропортПрилета"]->ToString(),
                reader["ВремяОтправления"]->ToString(),
                reader["ВремяПрибытия"]->ToString(),
                reader["ВремяВпути"]->ToString()
            );
            found = true;
        }

        reader->Close();
        sqlConnection->Close();

        if (!found)
        {
            LoadFlights();
            MessageBox::Show("Рейс или самолет с заданным Id не найден.", "Поиск не дал результатов", MessageBoxButtons::OK, MessageBoxIcon::Information);
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
        if (e->ColumnIndex == dataGridViewFlights->Columns["IdСамолета"]->Index)
        {
            String^ flightNumber = dataGridViewFlights->Rows[e->RowIndex]->Cells["Номер"]->Value->ToString();
            String^ newAirplaneId = dataGridViewFlights->Rows[e->RowIndex]->Cells["IdСамолета"]->Value->ToString();

            SqlConnection^ sqlConnection = gcnew SqlConnection("Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;");
            SqlCommand^ command = gcnew SqlCommand("UpdateAirplaneId", sqlConnection);
            command->CommandType = CommandType::StoredProcedure;

            command->Parameters->AddWithValue("@FlightId", flightNumber);
            command->Parameters->AddWithValue("@NewAirplaneId", newAirplaneId);

            try
            {
                sqlConnection->Open();
                command->ExecuteNonQuery();
                MessageBox::Show("Id самолета успешно обновлен.", "Успех", MessageBoxButtons::OK, MessageBoxIcon::Information);

                dataGridViewFlights->Rows[e->RowIndex]->Cells["IdСамолета"]->Tag = newAirplaneId;

                dataGridViewFlights->Rows[e->RowIndex]->Cells["IdСамолета"]->Value = newAirplaneId;
            }
            catch (SqlException^ ex)
            {
                MessageBox::Show("Ошибка при обновлении IdСамолета: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);

                dataGridViewFlights->Rows[e->RowIndex]->Cells["IdСамолета"]->Value = originalAirplaneId;
            }

            finally
            {
                sqlConnection->Close();
            }
        }
    }

    void TechFlight::dataGridViewFlights_CellBeginEdit(System::Object^ sender, System::Windows::Forms::DataGridViewCellCancelEventArgs^ e)
    {
        if (e->ColumnIndex == dataGridViewFlights->Columns["IdСамолета"]->Index)
        {
            originalAirplaneId = dataGridViewFlights->Rows[e->RowIndex]->Cells["IdСамолета"]->Value->ToString();

            dataGridViewFlights->Rows[e->RowIndex]->Cells["IdСамолета"]->Tag = originalAirplaneId;
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
            status = reader["Статус"]->ToString();
        }
        else
        {
            status = "Статус не найден"; 
        }

        reader->Close();

        return status;
    }

    System::Data::DataTable^ TechFlight::GetAvailableAirplanes()
    {
        System::Data::DataTable^ availableAirplanes = gcnew System::Data::DataTable();
        availableAirplanes->Columns->Add("Id");
        availableAirplanes->Columns->Add("Статус"); 

        String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
        SqlConnection^ sqlConnection = gcnew SqlConnection(connectionString);
        SqlCommand^ command = gcnew SqlCommand("SELECT Id, Статус FROM Самолет", sqlConnection);

        try
        {
            sqlConnection->Open();
            SqlDataReader^ reader = command->ExecuteReader();

            while (reader->Read())
            {
                System::Data::DataRow^ row = availableAirplanes->NewRow();
                row["Id"] = reader["Id"];
                row["Статус"] = reader["Статус"]; 
                availableAirplanes->Rows->Add(row);
            }

            reader->Close();
        }
        catch (Exception^ ex)
        {
            MessageBox::Show("Ошибка при загрузке доступных самолетов: " + ex->Message);
        }
        finally
        {
            sqlConnection->Close();
        }

        return availableAirplanes;
    }
}
