#include "BoardingPass.h"

namespace Airport
{
    BoardingPassForm::BoardingPassForm()
    {
        InitializeComponent();
        LoadBoardingPass();
    }

    BoardingPassForm::~BoardingPassForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void BoardingPassForm::InitializeComponent(void)
    {
		this->components = gcnew System::ComponentModel::Container();
		this->BackColor = System::Drawing::Color::White;

		int rightMargin = 20;
		int bottomMargin = 80;
		this->dataGridViewBoardingPass = gcnew DataGridView();
		this->dataGridViewBoardingPass->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
		this->dataGridViewBoardingPass->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
		this->dataGridViewBoardingPass->DefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewBoardingPass->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewBoardingPass->ColumnHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewBoardingPass->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewBoardingPass->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewBoardingPass->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
		this->dataGridViewBoardingPass->EnableHeadersVisualStyles = false;
		this->dataGridViewBoardingPass->GridColor = System::Drawing::Color::LightGray;
		this->dataGridViewBoardingPass->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dataGridViewBoardingPass->RowHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewBoardingPass->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewBoardingPass->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
		this->dataGridViewBoardingPass->Dock = System::Windows::Forms::DockStyle::Fill;
		this->dataGridViewBoardingPass->Margin = System::Windows::Forms::Padding(10);
		this->dataGridViewBoardingPass->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
		this->dataGridViewBoardingPass->BackgroundColor = System::Drawing::Color::White;
		this->dataGridViewBoardingPass->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewBoardingPass->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		this->dataGridViewBoardingPass->Location = System::Drawing::Point(20, 80);
		this->dataGridViewBoardingPass->Size = System::Drawing::Size(this->ClientSize.Width - this->dataGridViewBoardingPass->Location.X - rightMargin, this->ClientSize.Height - this->dataGridViewBoardingPass->Location.Y - bottomMargin);
		this->dataGridViewBoardingPass->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
		this->dataGridViewBoardingPass->Columns->Add("Id", "Номер талона");
		//this->dataGridViewBoardingPass->Columns->Add("IdПассажира", "Id пассажира");
		this->dataGridViewBoardingPass->Columns->Add("НомерБилета", "Номер билета");
		this->dataGridViewBoardingPass->Columns->Add("Место", "Место");
		this->dataGridViewBoardingPass->ReadOnly = true;
		this->dataGridViewBoardingPass->CellDoubleClick += gcnew DataGridViewCellEventHandler(this, &BoardingPassForm::dataGridViewBoardingPass_CellDoubleClick);

		this->Controls->Add(this->dataGridViewBoardingPass);

		this->txtId = gcnew MaterialSingleLineTextField();
		this->txtId->Hint = "Номер талона";
		this->txtId->ForeColor = System::Drawing::Color::Black;
		this->txtId->Location = System::Drawing::Point(20, 20);
		this->txtId->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtId);

		this->txtTicket = gcnew MaterialSingleLineTextField();
		this->txtTicket->Hint = "Номер билета";
		this->txtTicket->ForeColor = System::Drawing::Color::Black;
		this->txtTicket->Location = System::Drawing::Point(370, 20);
		this->txtTicket->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtTicket);

		this->btnSearch = gcnew MaterialFlatButton();
		this->btnSearch->Text = "Найти";
		this->btnSearch->Location = System::Drawing::Point(720, 15);
		this->btnSearch->Click += gcnew System::EventHandler(this, &BoardingPassForm::btnSearch_Click);
		this->Controls->Add(this->btnSearch);

		this->btnClear = gcnew MaterialFlatButton();
		this->btnClear->Text = "Очистить";
		this->btnClear->Location = System::Drawing::Point(btnSearch->Right + 20, 15);
		this->btnClear->Click += gcnew System::EventHandler(this, &BoardingPassForm::btnClear_Click);
		this->Controls->Add(this->btnClear);

		this->panelButtons = gcnew System::Windows::Forms::Panel();
		this->panelButtons->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->panelButtons->Height = 60; 
		this->panelButtons->Size = System::Drawing::Size(300, 60);
		this->panelButtons->Location = System::Drawing::Point(800, 100);

		this->btnEdit = gcnew MaterialRaisedButton();
		this->btnEdit->Text = "Создать талон";
		this->btnEdit->Size = System::Drawing::Size(120, 40);
		this->btnEdit->Click += gcnew EventHandler(this, &BoardingPassForm::btnEdit_Click);

		this->btnDelete = gcnew MaterialRaisedButton();
		this->btnDelete->Text = "Удалить";
		this->btnDelete->Click += gcnew System::EventHandler(this, &BoardingPassForm::btnDelete_Click);
		this->btnDelete->Size = System::Drawing::Size(120, 40);

		this->btnEdit->Location = System::Drawing::Point(600, 10); 
		this->btnDelete->Location = System::Drawing::Point(740, 10);
		this->panelButtons->Controls->Add(this->btnEdit);
		this->panelButtons->Controls->Add(this->btnDelete);
		this->Controls->Add(this->panelButtons);
	}

    void BoardingPassForm::LoadBoardingPass()
    {
		dataGridViewBoardingPass->Rows->Clear();

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand("SELECT * FROM ПосадочныйТалон", sqlConnection);

		sqlConnection->Open();
		SqlDataReader^ reader = command->ExecuteReader();

		while (reader->Read())
		{
			dataGridViewBoardingPass->Rows->Add(
				reader["Id"]->ToString(),
				reader["НомерБилета"]->ToString(),
				reader["Место"]->ToString()
			);
		}

		reader->Close();
		sqlConnection->Close();
    }

	void BoardingPassForm::dataGridViewBoardingPass_CellDoubleClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		Form^ makePassForm = gcnew MakeNewPassForm(this->dataGridViewBoardingPass->Rows[e->RowIndex]->Cells["НомерБилета"]->Value->ToString());

		makePassForm->Show();

		Form^ makeBaggageForm = gcnew MakeNewBaggageForm(this->dataGridViewBoardingPass->Rows[e->RowIndex]->Cells["Id"]->Value->ToString());

		makeBaggageForm->Show();
	}

	void BoardingPassForm::btnEdit_Click(Object^ sender, EventArgs^ e)
	{
		Form^ makePassForm = gcnew MakeNewPassForm();

		makePassForm->Show();
	}

	void BoardingPassForm::btnDelete_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (dataGridViewBoardingPass->SelectedRows->Count == 0)
		{
			MessageBox::Show("Пожалуйста, выберите талон для удаления.", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		int rowIndex = dataGridViewBoardingPass->SelectedRows[0]->Index;
		String^ ticketNumber = dataGridViewBoardingPass->Rows[rowIndex]->Cells["Id"]->Value->ToString();

		System::Windows::Forms::DialogResult result = MessageBox::Show("Вы уверены, что хотите удалить этот талон?", "Удалить талон", MessageBoxButtons::YesNo, MessageBoxIcon::Warning);

		if (result == System::Windows::Forms::DialogResult::Yes)
		{
			String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
			SqlConnection^ sqlConnection = gcnew SqlConnection(connectionString);

			SqlCommand^ command = gcnew SqlCommand("DELETE FROM ПосадочныйТалон WHERE Id = @ticketNumber", sqlConnection);
			command->Parameters->AddWithValue("@ticketNumber", ticketNumber);

			try
			{
				sqlConnection->Open();
				int rowsAffected = command->ExecuteNonQuery();

				if (rowsAffected > 0)
				{
					// Remove the row from the DataGridView if deletion was successful
					dataGridViewBoardingPass->Rows->RemoveAt(rowIndex);
					MessageBox::Show("Талон был успешно удалён.", "Удаление успешно", MessageBoxButtons::OK, MessageBoxIcon::Information);
				}
				else
				{
					MessageBox::Show("Не удалось удалить талон. Попробуйте снова.", "Ошибка удаления", MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			catch (Exception^ ex)
			{
				MessageBox::Show("Ошибка при удалении талона: " + ex->Message, "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			finally
			{
				sqlConnection->Close();
			}
		}
	}

	void BoardingPassForm::btnSearch_Click(System::Object^ sender, System::EventArgs^ e)
	{
		dataGridViewBoardingPass->Rows->Clear();

		String^ idFilter = txtId->Text->Trim();
		String^ ticketFilter = txtTicket->Text->Trim();

		if (String::IsNullOrEmpty(idFilter) && String::IsNullOrEmpty(ticketFilter)) {
			LoadBoardingPass();
			return;
		}

		String^ query = "SELECT * FROM ПосадочныйТалон WHERE 1=1";

		if (!String::IsNullOrEmpty(idFilter))
		{
			query += " AND Id LIKE @idFilter";
		}
		if (!String::IsNullOrEmpty(ticketFilter))
		{
			query += " AND НомерБилета LIKE @ticketFilter";
		}

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		SqlConnection^ sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand(query, sqlConnection);

		if (!String::IsNullOrEmpty(idFilter))
		{
			command->Parameters->AddWithValue("@idFilter", "%" + idFilter + "%");
		}
		if (!String::IsNullOrEmpty(ticketFilter))
		{
			command->Parameters->AddWithValue("@ticketFilter", "%" + ticketFilter + "%");
		}

		sqlConnection->Open();
		SqlDataReader^ reader = command->ExecuteReader();

		bool found = false;

		while (reader->Read())
		{
			dataGridViewBoardingPass->Rows->Add(
				reader["Id"]->ToString(),
				reader["НомерБилета"]->ToString(),
				reader["Место"]->ToString()
			);
			found = true;
		}

		reader->Close();
		sqlConnection->Close();

		if (!found)
		{
			LoadBoardingPass();
			MessageBox::Show("Номер талона или номер билета, соответствующий заданным параметрам, не найдены.", "Поиск не дал результатов", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	}

	void BoardingPassForm::btnClear_Click(System::Object^ sender, System::EventArgs^ e)
	{
		txtId->Text = "";
		txtTicket->Text = "";

		LoadBoardingPass();
	}
}

