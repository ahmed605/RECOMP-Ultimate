//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"
#include <wrl.h>
#include <windows.ui.h>
#include <windows.ui.composition.h>
#include <windows.ui.viewmanagement.h>
#include <windows.foundation.numerics.h>

using namespace Microsoft::WRL;

namespace RECompWRL
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		ComPtr<ABI::Windows::UI::Composition::IContainerVisual> visual;
		ComPtr<ABI::Windows::UI::Composition::ICompositor> compositor;
		ComPtr<ABI::Windows::UI::ViewManagement::IApplicationView> view;

		const static int size = 6;
		const static int columnGrid = 99;
		ABI::Windows::Foundation::Numerics::Vector2 sizeVector = ABI::Windows::Foundation::Numerics::Vector2 { size, size };

		void Page_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void Draw_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
