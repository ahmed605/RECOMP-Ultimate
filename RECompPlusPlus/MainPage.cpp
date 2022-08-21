#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.System.Threading.h>
#include <winrt/Windows.Foundation.h>
#include <iomanip>

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::UI::Composition;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI::ViewManagement;
using namespace Windows::Foundation;

namespace winrt::RECompPlusPlus::implementation
{
    ContainerVisual visual { nullptr };
    Compositor compositor { nullptr };
    ApplicationView view { nullptr };

    static int f = 0;
    static int size = 6;
    static int columnGrid = 99;
    float2 sizeVector = float2(size);

    MainPage::MainPage()
    {
        InitializeComponent();
    }

    void MainPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        compositor = Window::Current().Compositor();
        visual = compositor.CreateContainerVisual();
        ElementCompositionPreview::SetElementChildVisual(CompRect(), visual);
        view = ApplicationView::GetForCurrentView();
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

    IAsyncAction MainPage::Draw_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        co_await Windows::System::Threading::ThreadPool::RunAsync([&, this](Windows::Foundation::IAsyncAction const& workItem)
        {
                visual.Children().RemoveAll();

                view.Title(L"Creating visuals....");

                auto start_time = my_clock::now();
                
                for (int i = 0; i < columnGrid; i++)
                {
                    for (int j = 0; j < columnGrid + 1; j++) // 100 controls instead of 99
                    {
                        SpriteVisual b = compositor.CreateSpriteVisual();
                        b.Size(sizeVector);
                        //Random may slow down a bit, but it's for visual
                        //To test controls generation speed properly, please set a fixed color.
                        b.Brush(compositor.CreateColorBrush(ColorHelper::FromArgb(0xff, rand() % 256, rand() % 256, rand() % 256)));
                        b.Offset(float3(i * size, j * size, 0));
                        visual.Children().InsertAtBottom(b);
                    }
                }

                auto end_time = my_clock::now();

                auto diff = end_time - start_time;
                auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(diff);

                view.Title(L"Visuals created in: " + format_duration(milliseconds));
        });
    }
}
