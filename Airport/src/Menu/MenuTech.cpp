#include "MenuTech.h"

namespace Airport
{
	MenuTechForm::MenuTechForm(void)
	{
		InitializeComponent();
	}

	MenuTechForm::~MenuTechForm()
	{
		if (components)
		{
			delete components;
		}
	}

	void MenuTechForm::InitializeComponent(void)
	{
		this->components = gcnew System::ComponentModel::Container();
		System::Drawing::Icon^ icon = gcnew System::Drawing::Icon("main_logo.ico");
		this->Icon = icon;
		this->Text = "������� ����: ����������";
		this->Size = System::Drawing::Size(1500, 1000);
		this->StartPosition = FormStartPosition::CenterScreen;
		this->Name = "MenuTechForm";

		tabControl = gcnew MaterialTabControl();
		tabControl->Dock = DockStyle::Fill;
		tabControl->BackColor = System::Drawing::Color::White;
		tabControl->ForeColor = System::Drawing::Color::Black;

		tabSelector = gcnew MaterialTabSelector();
		tabSelector->Dock = DockStyle::Top;
		tabSelector->BaseTabControl = tabControl;
		tabSelector->BackColor = System::Drawing::Color::White;
		tabSelector->ForeColor = System::Drawing::Color::Black;

		flightsTab = gcnew TabPage("�����");
		tabControl->TabPages->Add(flightsTab);

		depBoardTab = gcnew TabPage("����� ������");
		tabControl->TabPages->Add(depBoardTab);

		arBoardTab = gcnew TabPage("����� �������");
		tabControl->TabPages->Add(arBoardTab);

		airplaneTab = gcnew TabPage("��������");
		tabControl->TabPages->Add(airplaneTab);

		Form^ TechFlightsForm = gcnew TechFlight();
		TechFlightsForm->TopLevel = false;
		TechFlightsForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		TechFlightsForm->Dock = DockStyle::Fill;
		flightsTab->Controls->Add(TechFlightsForm);
		TechFlightsForm->Show();

		Form^ depBoardForm = gcnew DepartureBoardForm();
		depBoardForm->TopLevel = false;
		depBoardForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		depBoardForm->Dock = DockStyle::Fill;
		depBoardTab->Controls->Add(depBoardForm);
		depBoardForm->Show();

		Form^ arBoardForm = gcnew ArrivalBoardForm();
		arBoardForm->TopLevel = false;
		arBoardForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		arBoardForm->Dock = DockStyle::Fill;
		arBoardTab->Controls->Add(arBoardForm);
		arBoardForm->Show();

		Form^ airplanesForm = gcnew AirplanesForm();
		airplanesForm->TopLevel = false;
		airplanesForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		airplanesForm->Dock = DockStyle::Fill;
		airplaneTab->Controls->Add(airplanesForm);
		airplanesForm->Show();

		Label^ lblDispatcher = gcnew Label();
		lblDispatcher->Text = "����������";
		lblDispatcher->Font = gcnew System::Drawing::Font("Roboto", 14, System::Drawing::FontStyle::Bold);
		lblDispatcher->AutoSize = true; lblDispatcher->AutoSize = true;
		lblDispatcher->Dock = DockStyle::Top;
		lblDispatcher->Location = System::Drawing::Point(this->ClientSize.Width - lblDispatcher->Width - 90, 10);
		lblDispatcher->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);
		lblDispatcher->BackColor = System::Drawing::Color::FromArgb(55, 71, 79);
		lblDispatcher->ForeColor = System::Drawing::Color::White;
		this->Controls->Add(lblDispatcher);
		lblDispatcher->BringToFront();

		this->Controls->Add(tabControl);
		this->Controls->Add(tabSelector);
	}
}
