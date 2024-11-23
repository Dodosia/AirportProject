#include "Baggage.h"

namespace Airport
{
	BaggageForm::BaggageForm(void)
	{
		InitializeComponent();
		LoadBaggage();
	}

	BaggageForm::~BaggageForm()
	{
		if (components)
		{
			delete components;
		}
	}

	void BaggageForm::InitializeComponent(void)
	{
		this->components = gcnew System::ComponentModel::Container();
		this->BackColor = System::Drawing::Color::White;

		int rightMargin = 20;
		int bottomMargin = 80;
		this->dataGridViewBaggage = gcnew DataGridView();
		this->dataGridViewBaggage->CellBorderStyle = System::Windows::Forms::DataGridViewCellBorderStyle::None;
		this->dataGridViewBaggage->AlternatingRowsDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
		this->dataGridViewBaggage->DefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewBaggage->DefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewBaggage->ColumnHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewBaggage->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::White;
		this->dataGridViewBaggage->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewBaggage->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
		this->dataGridViewBaggage->EnableHeadersVisualStyles = false;
		this->dataGridViewBaggage->GridColor = System::Drawing::Color::LightGray;
		this->dataGridViewBaggage->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
		this->dataGridViewBaggage->RowHeadersDefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewBaggage->DefaultCellStyle->SelectionBackColor = System::Drawing::Color::LightBlue;
		this->dataGridViewBaggage->DefaultCellStyle->SelectionForeColor = System::Drawing::Color::Black;
		this->dataGridViewBaggage->Dock = System::Windows::Forms::DockStyle::Fill;
		this->dataGridViewBaggage->Margin = System::Windows::Forms::Padding(10);
		this->dataGridViewBaggage->Font = gcnew System::Drawing::Font("Arial", 14, System::Drawing::FontStyle::Regular);
		this->dataGridViewBaggage->BackgroundColor = System::Drawing::Color::White;
		this->dataGridViewBaggage->ForeColor = System::Drawing::Color::Black;
		this->dataGridViewBaggage->AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode::Fill;
		this->dataGridViewBaggage->Location = System::Drawing::Point(20, 80);
		this->dataGridViewBaggage->Size = System::Drawing::Size(this->ClientSize.Width - this->dataGridViewBaggage->Location.X - rightMargin, this->ClientSize.Height - this->dataGridViewBaggage->Location.Y - bottomMargin);
		this->dataGridViewBaggage->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Bottom | AnchorStyles::Left | AnchorStyles::Right);
		this->dataGridViewBaggage->Columns->Add("Id", "����� �����");
		this->dataGridViewBaggage->Columns->Add("Id������", "����� ������");
		this->dataGridViewBaggage->Columns->Add("���", "���");
		this->dataGridViewBaggage->Columns->Add("��������", "��������");
		this->dataGridViewBaggage->ReadOnly = true;
		this->dataGridViewBaggage->CellDoubleClick += gcnew DataGridViewCellEventHandler(this, &BaggageForm::dataGridViewBaggage_CellDoubleClick);

		this->Controls->Add(this->dataGridViewBaggage);

		this->txtId = gcnew MaterialSingleLineTextField();
		this->txtId->Hint = "����� �����";
		this->txtId->ForeColor = System::Drawing::Color::Black;
		this->txtId->Location = System::Drawing::Point(20, 20);
		this->txtId->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtId);

		this->txtTalon = gcnew MaterialSingleLineTextField();
		this->txtTalon->Hint = "����� ������";
		this->txtTalon->ForeColor = System::Drawing::Color::Black;
		this->txtTalon->Location = System::Drawing::Point(370, 20);
		this->txtTalon->Size = System::Drawing::Size(300, 20);
		this->Controls->Add(this->txtTalon);

		this->btnSearch = gcnew MaterialFlatButton();
		this->btnSearch->Text = "�����";
		this->btnSearch->Location = System::Drawing::Point(720, 15);
		this->Controls->Add(this->btnSearch);

		this->panelButtons = gcnew System::Windows::Forms::Panel();
		this->panelButtons->Dock = System::Windows::Forms::DockStyle::Bottom;
		this->panelButtons->Height = 60;
		this->panelButtons->Size = System::Drawing::Size(300, 60);
		this->panelButtons->Location = System::Drawing::Point(800, 100);

		this->btnEdit = gcnew MaterialFlatButton();
		this->btnEdit->Text = "������� �����";
		this->btnEdit->Size = System::Drawing::Size(120, 40);
		this->btnEdit->Click += gcnew EventHandler(this, &BaggageForm::btnEdit_Click);

		this->btnDelete = gcnew MaterialFlatButton();
		this->btnDelete->Text = "�������";
		this->btnDelete->Size = System::Drawing::Size(120, 40);

		this->btnEdit->Location = System::Drawing::Point(600, 10);
		this->btnDelete->Location = System::Drawing::Point(740, 10);
		this->panelButtons->Controls->Add(this->btnEdit);
		this->panelButtons->Controls->Add(this->btnDelete);
		this->Controls->Add(this->panelButtons);
	}

	void BaggageForm::LoadBaggage()
	{
		dataGridViewBaggage->Rows->Clear();

		String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
		sqlConnection = gcnew SqlConnection(connectionString);
		SqlCommand^ command = gcnew SqlCommand("SELECT * FROM �����", sqlConnection);

		sqlConnection->Open();
		SqlDataReader^ reader = command->ExecuteReader();

		while (reader->Read())
		{
			dataGridViewBaggage->Rows->Add(
				reader["Id"]->ToString(),
				reader["Id������"]->ToString(),
				reader["���"]->ToString(),
				reader["��������"]->ToString()
			);
		}

		reader->Close();
		sqlConnection->Close();
	}

	void BaggageForm::dataGridViewBaggage_CellDoubleClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		if (e->RowIndex >= 0)
		{
			String^ id = this->dataGridViewBaggage->Rows[e->RowIndex]->Cells["Id"]->Value->ToString();
			String^ talon = this->dataGridViewBaggage->Rows[e->RowIndex]->Cells["Id������"]->Value->ToString();
			String^ weight = this->dataGridViewBaggage->Rows[e->RowIndex]->Cells["���"]->Value->ToString();
			String^ dicr = this->dataGridViewBaggage->Rows[e->RowIndex]->Cells["��������"]->Value->ToString();

			Form^ makePassForm = gcnew MakeBaggageForm(id, talon, weight, dicr);

			makePassForm->Show();
		}
	}

	void BaggageForm::btnEdit_Click(Object^ sender, EventArgs^ e)
	{
		Form^ makePassForm = gcnew MakeNewBaggageForm();

		makePassForm->Show();
	}
}