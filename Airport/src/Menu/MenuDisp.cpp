#include "MenuDisp.h"

namespace Airport
{
    MenuDispForm::MenuDispForm(void)
    {
        InitializeComponent();
    }

    MenuDispForm::~MenuDispForm()
    {
        if (components)
        {
            delete components;
        }
    }

    void MenuDispForm::InitializeComponent(void)
    {
		this->components = gcnew System::ComponentModel::Container();
		System::Drawing::Icon^ icon = gcnew System::Drawing::Icon("main_logo.ico");
		this->Icon = icon;
		this->Text = "Главное меню: Авиадиспетчер";
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

		Form^ airportForm = gcnew AirportsForm();
		airportForm->TopLevel = false;
		airportForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
		airportForm->Dock = DockStyle::Fill;
		airportTab->Controls->Add(airportForm);
		airportForm->Show();

		this->Controls->Add(tabControl);
		this->Controls->Add(tabSelector);

		Label^ lblDispatcher = gcnew Label();
		lblDispatcher->Text = "АВИАДИСПЕТЧЕР";
		lblDispatcher->Font = gcnew System::Drawing::Font("Roboto", 14, System::Drawing::FontStyle::Bold);
		lblDispatcher->AutoSize = true; lblDispatcher->AutoSize = true;
		lblDispatcher->Dock = DockStyle::Top;
		lblDispatcher->Location = System::Drawing::Point(this->ClientSize.Width - lblDispatcher->Width - 100, 10);
		lblDispatcher->Anchor = static_cast<AnchorStyles>(AnchorStyles::Top | AnchorStyles::Right);
		lblDispatcher->BackColor = System::Drawing::Color::FromArgb(55, 71, 79);
		lblDispatcher->ForeColor = System::Drawing::Color::White;
		this->Controls->Add(lblDispatcher);
		lblDispatcher->BringToFront();
    }

}
