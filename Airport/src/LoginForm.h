#pragma once
#include <Windows.h>
#include <gdiplus.h>

#include "Menu/MenuAgent.h"
#include "Menu/MenuTech.h"
#include "Menu/MenuDisp.h"

#pragma comment (lib, "User32.lib")
#pragma comment (lib, "Gdi32.lib")
#pragma comment (lib, "Gdiplus.lib")

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace Gdiplus;
using namespace MaterialSkin;
using namespace MaterialSkin::Controls;
using namespace System::Drawing::Imaging;
using namespace System::Drawing::Drawing2D;

namespace Airport
{
	public ref class EntryPoint : public System::Windows::Forms::Form
	{
	public:
		EntryPoint(void);
		~EntryPoint();
	protected:
		virtual void OnPaint(PaintEventArgs^ e) override;
	private:
		void InitializeComponent(void);
		void OnMyButtonClick(Object^ sender, EventArgs^ e);

		System::Drawing::Bitmap^ backgroundImage;
		System::Drawing::Point dragCursorPoint;
		System::Drawing::Point dragFormPoint;
		IContainer^ components;
	};
}
