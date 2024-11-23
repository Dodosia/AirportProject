#include "MenuAgent.h"

namespace Airport
{
	MenuAgentForm::MenuAgentForm(void)
	{
		InitializeComponent();
	}

	MenuAgentForm::~MenuAgentForm()
	{
		if (components)
		{
			delete components;
		}
	}

	void MenuAgentForm::InitializeComponent(void)
	{
		this->components = gcnew System::ComponentModel::Container();
		System::Drawing::Icon^ icon = gcnew System::Drawing::Icon("main_logo.ico");
		this->Icon = icon;
		this->Text = "Главное меню: Агент регистрации";
		this->Size = System::Drawing::Size(1500, 1000);
		this->StartPosition = FormStartPosition::CenterScreen;

		tabControl = gcnew MaterialTabControl();
		tabControl->Dock = DockStyle::Fill;
		tabControl->BackColor = System::Drawing::Color::White;
		tabControl->ForeColor = System::Drawing::Color::Black;

		tabSelector = gcnew MaterialTabSelector();
		tabSelector->Dock = DockStyle::Top;
		tabSelector->BaseTabControl = tabControl;
		tabSelector->BackColor = System::Drawing::Color::White;  // Set background color of the tab selector
		tabSelector->ForeColor = System::Drawing::Color::Black;
		
		flightsTab = gcnew TabPage("Рейсы");
		tabControl->TabPages->Add(flightsTab);

		passangersTab = gcnew TabPage("Пассажиры");
		tabControl->TabPages->Add(passangersTab);

		boardingPassTab = gcnew TabPage("Посадочный талон");
		tabControl->TabPages->Add(boardingPassTab);

		ticketsTab = gcnew TabPage("Билеты");
		tabControl->TabPages->Add(ticketsTab);

		baggageTab = gcnew TabPage("Багаж");
		tabControl->TabPages->Add(baggageTab);
	
		Form^ flightsForm = gcnew FlightsForm();
		flightsForm->TopLevel = false;
		flightsForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		flightsForm->Dock = DockStyle::Fill;
		flightsTab->Controls->Add(flightsForm);
		flightsForm->Show();

		Form^ passangersForm = gcnew PassangersForm();
		passangersForm->TopLevel = false;
		passangersForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		passangersForm->Dock = DockStyle::Fill;
		passangersTab->Controls->Add(passangersForm);
		passangersForm->Show();

		Form^ ticketsForm = gcnew TicketsForm();
		ticketsForm->TopLevel = false;
		ticketsForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		ticketsForm->Dock = DockStyle::Fill;
		ticketsTab->Controls->Add(ticketsForm);
		ticketsForm->Show();

		Form^ boardingPassForm = gcnew BoardingPassForm();
		boardingPassForm ->TopLevel = false;
		boardingPassForm ->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		boardingPassForm ->Dock = DockStyle::Fill;
		boardingPassTab->Controls->Add(boardingPassForm);
		boardingPassForm->Show();

		Form^ baggageForm = gcnew BaggageForm();
		baggageForm->TopLevel = false;
		baggageForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		baggageForm->Dock = DockStyle::Fill;
		baggageTab->Controls->Add(baggageForm);
		baggageForm->Show();

		this->Controls->Add(tabControl);
		this->Controls->Add(tabSelector);

		Label^ lblDispatcher = gcnew Label();
		lblDispatcher->Text = "АГЕНТ РЕГИСТРАЦИИ";
		lblDispatcher->Font = gcnew System::Drawing::Font("Roboto", 14, System::Drawing::FontStyle::Bold);
		lblDispatcher->AutoSize = true; lblDispatcher->AutoSize = true;
		lblDispatcher->Dock = DockStyle::Top;
		lblDispatcher->Location = System::Drawing::Point(this->ClientSize.Width - lblDispatcher->Width - 150, 10);
		lblDispatcher->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);
		lblDispatcher->BackColor = System::Drawing::Color::FromArgb(55, 71, 79);
		lblDispatcher->ForeColor = System::Drawing::Color::White;
		this->Controls->Add(lblDispatcher);
		lblDispatcher->BringToFront();
	}
}
