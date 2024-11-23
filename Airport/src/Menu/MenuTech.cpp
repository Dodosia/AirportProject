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
		this->Text = "Главное меню: Авиатехник";
		this->Size = System::Drawing::Size(1500, 1000);
		this->StartPosition = FormStartPosition::CenterScreen;

		tabControl = gcnew MaterialTabControl();
		tabControl->Dock = DockStyle::Fill;
		tabControl->BackColor = System::Drawing::Color::White;
		tabControl->ForeColor = System::Drawing::Color::Black;

		tabSelector = gcnew MaterialTabSelector();
		tabSelector->Dock = DockStyle::Top;
		tabSelector->BaseTabControl = tabControl;
		tabSelector->BackColor = System::Drawing::Color::White;
		tabSelector->ForeColor = System::Drawing::Color::Black;

		flightsTab = gcnew TabPage("Рейсы");
		tabControl->TabPages->Add(flightsTab);

		depBoardTab = gcnew TabPage("Табло вылета");
		tabControl->TabPages->Add(depBoardTab);

		arBoardTab = gcnew TabPage("Табло прилета");
		tabControl->TabPages->Add(arBoardTab);

		airplaneTab = gcnew TabPage("Самолеты");
		tabControl->TabPages->Add(airplaneTab);

		airportTab = gcnew TabPage("Аэропорты");
		tabControl->TabPages->Add(airportTab);

		Form^ flightsForm = gcnew FlightsForm();
		flightsForm->TopLevel = false;
		flightsForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		flightsForm->Dock = DockStyle::Fill;
		flightsTab->Controls->Add(flightsForm);
		flightsForm->Show();

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

		Form^ airportForm = gcnew AirportsForm();
		airportForm->TopLevel = false;
		airportForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		airportForm->Dock = DockStyle::Fill;
		airportTab->Controls->Add(airportForm);
		airportForm->Show();

		Label^ lblDispatcher = gcnew Label();
		lblDispatcher->Text = "АВИАТЕХНИК";
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
