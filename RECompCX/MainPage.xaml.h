//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include <WindowsNumerics.h>

using namespace Windows::UI;
using namespace Windows::UI::Composition;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml::Hosting;

namespace RECompCX
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		ContainerVisual^ visual;
		Compositor^ compositor;
		ApplicationView^ view;

		const static int size = 6;
		const static int columnGrid = 99;
		Windows::Foundation::Numerics::float2 sizeVector = Windows::Foundation::Numerics::float2::float2(size);

		void Draw_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
