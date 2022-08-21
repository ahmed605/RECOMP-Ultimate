//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace RECompWRL;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Composition;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Hosting;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}


void RECompWRL::MainPage::Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	compositor = reinterpret_cast<ABI::Windows::UI::Composition::ICompositor*>(Window::Current->Compositor);
	compositor->CreateContainerVisual(visual.GetAddressOf());
	ElementCompositionPreview::SetElementChildVisual(CompRect, reinterpret_cast<Visual^>(visual.Get()));
	view = reinterpret_cast<ABI::Windows::UI::ViewManagement::IApplicationView*>(ApplicationView::GetForCurrentView());
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


void RECompWRL::MainPage::Draw_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto workItem = ref new Windows::System::Threading::WorkItemHandler(
		[&, this](IAsyncAction^ workItem)
		{
			ComPtr<ABI::Windows::UI::Composition::IVisualCollection> collection;

			visual->get_Children(collection.GetAddressOf());
			collection->RemoveAll();

			view->put_Title(reinterpret_cast<HSTRING>((String^)"Creating visuals...."));

			auto start_time = my_clock::now();

			for (int i = 0; i < columnGrid; i++)
			{
				for (int j = 0; j < columnGrid + 1; j++) // 100 controls instead of 99
				{
					ComPtr<ABI::Windows::UI::Composition::ISpriteVisual> b;
					compositor->CreateSpriteVisual(b.GetAddressOf());

					ComPtr<ABI::Windows::UI::Composition::IVisual> bVisual;
					b.As<ABI::Windows::UI::Composition::IVisual>(&bVisual);

					bVisual->put_Size(sizeVector);
					//Random may slow down a bit, but it's for visual
					//To test controls generation speed properly, please set a fixed color.
					ComPtr<ABI::Windows::UI::Composition::ICompositionColorBrush> brush;
					compositor->CreateColorBrushWithColor(ABI::Windows::UI::Color{ 0xff, (BYTE) (rand() % 256), (BYTE)(rand() % 256), (BYTE)(rand() % 256) }, brush.GetAddressOf());
					
					ComPtr<ABI::Windows::UI::Composition::ICompositionBrush> compBrush;
					brush.As<ABI::Windows::UI::Composition::ICompositionBrush>(&compBrush);
					b->put_Brush(compBrush.Get());
					bVisual->put_Offset(ABI::Windows::Foundation::Numerics::Vector3{ (FLOAT) (i * size), (FLOAT)(j * size), 0 });
					collection->InsertAtBottom(bVisual.Get());
				}
			}

			auto end_time = my_clock::now();

			auto diff = end_time - start_time;
			auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

			view->put_Title(reinterpret_cast<HSTRING>(ref new String((L"Visuals created in: " + format_duration(milliseconds)).c_str())));
		});

	auto asyncAction = Windows::System::Threading::ThreadPool::RunAsync(workItem);
}
