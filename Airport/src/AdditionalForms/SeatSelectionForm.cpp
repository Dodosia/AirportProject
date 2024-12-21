#include "SeatSelectionForm.h"

namespace Airport
{
    SeatSelectionForm::SeatSelectionForm(MakeNewPassForm^ parent) : parentForm(parent)
    {
        InitializeComponent();
        CreateSeatButtons();
    }

    void SeatSelectionForm::InitializeComponent()
    {
        this->Size = System::Drawing::Size(300, 850);
        this->BackColor = System::Drawing::Color::White;

        int x = parentForm->ClientSize.Width + 800;
        int y = parentForm->ClientSize.Height - 200;

        this->Location = System::Drawing::Point(x, y);
        this->StartPosition = FormStartPosition::Manual;

        seatPanel = gcnew Panel();
        seatPanel->Size = System::Drawing::Size(300, 800);
        seatPanel->Location = System::Drawing::Point(10, 10); 
        this->Controls->Add(seatPanel);
    }

    void SeatSelectionForm::CreateSeatButtons()
    {
        String^ connectionString = "Data Source=LAPTOP-FV01NO90;Initial Catalog=Aeroport;Integrated Security=True;";
        SqlConnection^ connection = gcnew SqlConnection(connectionString);

        String^ query = "EXEC GetOccupiedSeats @ticketId";
        SqlCommand^ command = gcnew SqlCommand(query, connection);
        //command->CommandType = CommandType::StoredProcedure;
        command->Parameters->AddWithValue("@ticketId", parentForm->txtTicketId->Text);

        SqlDataReader^ reader;
        connection->Open();
        reader = command->ExecuteReader();

        List<String^>^ occupiedSeats = gcnew List<String^>();

        while (reader->Read())
        {
            occupiedSeats->Add(reader["Место"]->ToString());
        }
        reader->Close();

        SqlCommand^ command2 = gcnew SqlCommand("FindAirplaneSeats", connection);
        command2->CommandType = CommandType::StoredProcedure;

        command2->Parameters->AddWithValue("@ticketId", Convert::ToInt32(parentForm->txtTicketId->Text));
        SqlParameter^ outputParam = gcnew SqlParameter("@seats", SqlDbType::Int);
        outputParam->Direction = ParameterDirection::Output;
        command2->Parameters->Add(outputParam);
        command2->ExecuteNonQuery();
        connection->Close();

        int capacity = Convert::ToInt32(outputParam->Value);
        int cols = 6;
        int rows = (capacity + cols - 1) / cols;
        int currentSeatIndex = 0;

        Panel^ firstClassPanel = gcnew Panel();
        firstClassPanel->Size = System::Drawing::Size(580, 150);
        firstClassPanel->Location = System::Drawing::Point(10, 40);
        firstClassPanel->AutoScroll = true;

        Panel^ businessClassPanel = gcnew Panel();
        businessClassPanel->Size = System::Drawing::Size(580, 150);
        businessClassPanel->Location = System::Drawing::Point(10, firstClassPanel->Bottom + 40);
        businessClassPanel->AutoScroll = true;

        Panel^ premiumEconomyClassPanel = gcnew Panel();
        premiumEconomyClassPanel->Size = System::Drawing::Size(580, 150);
        premiumEconomyClassPanel->Location = System::Drawing::Point(10, businessClassPanel->Bottom + 40);
        premiumEconomyClassPanel->AutoScroll = true;

        Panel^ economyClassPanel = gcnew Panel();
        economyClassPanel->Size = System::Drawing::Size(580, 150);
        economyClassPanel->Location = System::Drawing::Point(10, premiumEconomyClassPanel->Bottom + 40);
        economyClassPanel->AutoScroll = true;

        Label^ firstClassLabel = gcnew Label();
        firstClassLabel->Text = "Первый класс (F)";
        firstClassLabel->Location = System::Drawing::Point(10, 10); 
        firstClassLabel->Size = System::Drawing::Size(200, 20);
        firstClassLabel->Font = gcnew System::Drawing::Font("Arial", 10, System::Drawing::FontStyle::Bold);

        Label^ businessClassLabel = gcnew Label();
        businessClassLabel->Text = "Бизнес класс (C)";
        businessClassLabel->Location = System::Drawing::Point(10, firstClassPanel->Bottom + 20);
        businessClassLabel->Size = System::Drawing::Size(200, 20);
        businessClassLabel->Font = gcnew System::Drawing::Font("Arial", 10, System::Drawing::FontStyle::Bold);

        Label^ premiumEconomyClassLabel = gcnew Label();
        premiumEconomyClassLabel->Text = "Премиум эконом (W)";
        premiumEconomyClassLabel->Location = System::Drawing::Point(10, businessClassPanel->Bottom + 20);
        premiumEconomyClassLabel->Size = System::Drawing::Size(200, 20);
        premiumEconomyClassLabel->Font = gcnew System::Drawing::Font("Arial", 10, System::Drawing::FontStyle::Bold);

        Label^ economyClassLabel = gcnew Label();
        economyClassLabel->Text = "Эконом класс (Y)";
        economyClassLabel->Location = System::Drawing::Point(10, premiumEconomyClassPanel->Bottom + 20);
        economyClassLabel->Size = System::Drawing::Size(200, 20);
        economyClassLabel->Font = gcnew System::Drawing::Font("Arial", 10, System::Drawing::FontStyle::Bold);

        seatPanel->Controls->Add(firstClassLabel);
        seatPanel->Controls->Add(businessClassLabel);
        seatPanel->Controls->Add(premiumEconomyClassLabel);
        seatPanel->Controls->Add(economyClassLabel);

        int firstClassSeats = (int)(capacity * 0.05);        // 5% для первого класса
        int businessClassSeats = (int)(capacity * 0.15);     // 15% для бизнес класса
        int premiumEconomyClassSeats = (int)(capacity * 0.20); // 20% для премиум эконом
        int economyClassSeats = capacity - (firstClassSeats + businessClassSeats + premiumEconomyClassSeats); 

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                int seatNumber = currentSeatIndex + 1;
                if (seatNumber > capacity) break;

                Button^ btnSeat = gcnew Button();
                String^ seatLabel = (i + 1).ToString() + Char::ConvertFromUtf32('A' + j);
                btnSeat->Text = seatLabel;
                btnSeat->Size = System::Drawing::Size(25, 25);
                btnSeat->Location = System::Drawing::Point(30 * j, 30 * i);
                btnSeat->Click += gcnew EventHandler(this, &SeatSelectionForm::btnSeat_Click);

               
                if (seatNumber <= firstClassSeats)
                {
                    if (occupiedSeats->Contains(seatLabel))
                    {
                        btnSeat->BackColor = System::Drawing::Color::Red;
                    }
                    else
                    {
                        btnSeat->BackColor = System::Drawing::Color::Gold;
                    }

                    firstClassPanel->Controls->Add(btnSeat);
                }
                else if (seatNumber <= firstClassSeats + businessClassSeats)
                {
                    if (occupiedSeats->Contains(seatLabel))
                    {
                        btnSeat->BackColor = System::Drawing::Color::Red; // Занятое место — красное
                    }
                    else
                    {
                        btnSeat->BackColor = System::Drawing::Color::LightBlue;
                    }

                    businessClassPanel->Controls->Add(btnSeat);
                }
                else if (seatNumber <= firstClassSeats + businessClassSeats + premiumEconomyClassSeats)
                {
                    if (occupiedSeats->Contains(seatLabel))
                    {
                        btnSeat->BackColor = System::Drawing::Color::Red; // Занятое место — красное
                    }
                    else
                    {
                        btnSeat->BackColor = System::Drawing::Color::LightGreen;
                    }
                    
                    premiumEconomyClassPanel->Controls->Add(btnSeat);
                }
                else
                {
                    if (occupiedSeats->Contains(seatLabel))
                    {
                        btnSeat->BackColor = System::Drawing::Color::Red; // Занятое место — красное
                    }
                    else
                    {
                        btnSeat->BackColor = System::Drawing::Color::LightGray;
                    }
                    economyClassPanel->Controls->Add(btnSeat);
                }

                currentSeatIndex++;
            }

            if (currentSeatIndex >= capacity) break;
        }

        seatPanel->Controls->Add(firstClassPanel);
        seatPanel->Controls->Add(businessClassPanel);
        seatPanel->Controls->Add(premiumEconomyClassPanel);
        seatPanel->Controls->Add(economyClassPanel);
    }

    void SeatSelectionForm::btnSeat_Click(System::Object^ sender, System::EventArgs^ e)
    {
        Button^ btn = (Button^)sender;

        if (btn->BackColor == System::Drawing::Color::Red)
        {
            MessageBox::Show("Это место уже занято!", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
        else
        {
            parentForm->SetSelectedSeat(btn->Text);
            this->Close();
        }
    }
}