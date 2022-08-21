#pragma once

#include "MainPage.g.h"

using namespace winrt::Windows::Foundation;

namespace winrt::RECompPlusPlus::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        IAsyncAction Draw_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::RECompPlusPlus::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
