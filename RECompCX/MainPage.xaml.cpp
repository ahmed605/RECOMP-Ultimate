//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace RECompCX;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}

typedef std::chrono::high_resolution_clock my_clock;

std::wstring format_duration(std::chrono::milliseconds ms) {
	auto secs = std::chrono::duration_cast<std::chrono::seconds>(ms);
	ms -= std::chrono::duration_cast<std::chrono::milliseconds>(secs);
	auto mins = std::chrono::duration_cast<std::chrono::minutes>(secs);
	secs -= std::chrono::duration_cast<std::chrono::seconds>(mins);

	std::wstringstream ss;
	ss << std::setfill(L'0') << std::setw(2) << mins.count() << L":" << std::setfill(L'0')
		<< std::setw(2) << secs.count() << L"." << std::setfill(L'0') << std::setw(3) << ms.count();
	return ss.str();
}

void RECompCX::MainPage::Draw_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto workItem = ref new Windows::System::Threading::WorkItemHandler(
		[&, this](IAsyncAction^ workItem)
		{
			visual->Children->RemoveAll();

			view->Title = "Creating visuals....";

			auto start_time = my_clock::now();

			for (int i = 0; i < columnGrid; i++)
			{
				for (int j = 0; j < columnGrid + 1; j++) // 100 controls instead of 99
				{
					SpriteVisual^ b = compositor->CreateSpriteVisual();
					b->Size = sizeVector;
					//Random may slow down a bit, but it's for visual
					//To test controls generation speed properly, please set a fixed color.
					b->Brush = compositor->CreateColorBrush(ColorHelper::FromArgb(0xff, rand() % 256, rand() % 256, rand() % 256));
					b->Offset = Windows::Foundation::Numerics::float3::float3(i * size, j * size, 0);
					visual->Children->InsertAtBottom(b);
				}
			}

			auto end_time = my_clock::now();

			auto diff = end_time - start_time;
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

			view->Title = ref new String((L"Visuals created in: " + format_duration(milliseconds)).c_str());
		});

	auto asyncAction = Windows::System::Threading::ThreadPool::RunAsync(workItem);
}


void RECompCX::MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	compositor = Window::Current->Compositor;
	visual = compositor->CreateContainerVisual();
	ElementCompositionPreview::SetElementChildVisual(CompRect, visual);
	view = ApplicationView::GetForCurrentView();
}
