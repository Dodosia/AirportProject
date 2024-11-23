#include "Flights.h"

namespace Airport
{
	FlightsForm::FlightsForm(void)
	{
        InitializeComponent();
        LoadFlights();
	}

	FlightsForm::~FlightsForm()
	{
		if (components)
		{
			delete components;
		}
	}

	void FlightsForm::InitializeComponent(void)
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

        this->dataGridViewFlights->Columns->Add("Номер", "Номер");
        this->dataGridViewFlights->Columns->Add("IdСамолета", "Id Самолета");
        this->dataGridViewFlights->Columns->Add("АэропортВылета", "Аэропорт вылета");
        this->dataGridViewFlights->Columns->Add("АэропортПрилета", "Аэропорт прилета");
        this->dataGridViewFlights->Columns->Add("ВремяОтправления", "Время отправления");
        this->dataGridViewFlights->Columns->Add("ВремяПрибытия", "Время прибытия");
        this->dataGridViewFlights->Columns->Add("ВремяВпути", "Время в пути");
        this->dataGridViewFlights->ReadOnly = true;
 
        this->Controls->Add(this->dataGridViewFlights);

        this->txtNumber = gcnew MaterialSingleLineTextField();
        this->txtNumber->Hint = "Номер рейса";
        this->txtNumber->BackColor = System::Drawing::Color::Blue;
        this->txtNumber->ForeColor = System::Drawing::Color::Black;
        this->txtNumber->Location = System::Drawing::Point(350, 20);
        this->txtNumber->Size = System::Drawing::Size(300, 20);
        this->Controls->Add(this->txtNumber);

        this->txtAirport = gcnew MaterialSingleLineTextField();
        this->txtAirport->Hint = "Аэропорт прибытия";
        this->txtAirport->BackColor = System::Drawing::Color::Blue;
        this->txtAirport->ForeColor = System::Drawing::Color::Black;
        this->txtAirport->Location = System::Drawing::Point(20, 20);
        this->txtAirport->Size = System::Drawing::Size(300, 20);
        this->Controls->Add(this->txtAirport);

        this->btnSearch = gcnew MaterialFlatButton();
        this->btnSearch->Text = "Найти";
        this->btnSearch->Location = System::Drawing::Point(700, 15);
        this->Controls->Add(this->btnSearch);
	}


	void FlightsForm::LoadFlights()
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
}
