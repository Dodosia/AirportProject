#include "LoginForm.h"

namespace Airport
{
	EntryPoint::EntryPoint(void)
	{
		InitializeComponent();
		this->Text = L"Вход";
		backgroundImage = gcnew System::Drawing::Bitmap("vendor/icon/m_theme.jpg");
	}

	EntryPoint::~EntryPoint()
	{
		if (components)
		{
			delete components;
		}
	}

	void EntryPoint::OnPaint(PaintEventArgs^ e)
	{
		System::Drawing::Graphics^ g = e->Graphics;

		System::Drawing::Imaging::ImageAttributes^ attributes = gcnew System::Drawing::Imaging::ImageAttributes();

		g->DrawImage(backgroundImage,
			this->ClientRectangle,
			0, 0,
			backgroundImage->Width,
			backgroundImage->Height,
			GraphicsUnit::Pixel,
			attributes);
	}

	void EntryPoint::InitializeComponent(void)
	{
		this->Text = "Вход";
		this->Size = System::Drawing::Size(800, 600);
		this->StartPosition = FormStartPosition::CenterScreen;
		System::Drawing::Icon^ icon = gcnew System::Drawing::Icon("main_logo.ico");
		this->Icon = icon;

		PictureBox^ logoPictureBox = gcnew PictureBox();
		logoPictureBox->Image = gcnew System::Drawing::Bitmap("vendor/icon/logo.png");
		logoPictureBox->BackColor = System::Drawing::Color::Transparent;
		logoPictureBox->SizeMode = PictureBoxSizeMode::Zoom;
		logoPictureBox->Size = System::Drawing::Size(350, 350);
		logoPictureBox->Location = System::Drawing::Point((this->ClientSize.Width - logoPictureBox->Width) / 2, 0);
		logoPictureBox->Parent = this;
		logoPictureBox->BringToFront();
		this->Controls->Add(logoPictureBox);

		MaterialSingleLineTextField^ loginField = gcnew MaterialSingleLineTextField();
		loginField->Hint = "Логин";
		loginField->Size = System::Drawing::Size(200, 40);
		loginField->ForeColor = System::Drawing::Color::Black;
		loginField->Location = System::Drawing::Point((this->ClientSize.Width - loginField->Width) / 2, 350);
		this->Controls->Add(loginField);

		MaterialSingleLineTextField^ passwordField = gcnew MaterialSingleLineTextField();
		passwordField->Hint = "Пароль";
		passwordField->Size = System::Drawing::Size(200, 100);
		passwordField->ForeColor = System::Drawing::Color::Black;
		passwordField->PasswordChar = '*';
		passwordField->Location = System::Drawing::Point((this->ClientSize.Width - passwordField->Width) / 2, 400);
		this->Controls->Add(passwordField);

		MaterialFlatButton^ myButton = gcnew MaterialFlatButton();
		myButton->Text = "Войти";
		myButton->Location = System::Drawing::Point(360, 450);
		myButton->Size = System::Drawing::Size(100, 50);
		myButton->AutoSize = true;
		this->Controls->Add(myButton);
		myButton->Click += gcnew EventHandler(this, &EntryPoint::OnMyButtonClick);
	}

	void EntryPoint::OnMyButtonClick(Object^ sender, EventArgs^ e)
	{
		Form^ form = gcnew MenuAgentForm();
		form->Show();

		Form^ form2 = gcnew MenuTechForm();
		form2->Show();

		Form^ form3 = gcnew MenuDispForm();
		form3->Show();
	}
}

