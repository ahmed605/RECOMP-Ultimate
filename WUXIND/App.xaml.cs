using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.ApplicationModel.Core;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI;
using Windows.UI.Composition;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Hosting;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Xaml.Shapes;

namespace WUXIND
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    public partial class App : Application
    {
        ContainerVisual visual;
        Compositor compositor;
        ApplicationView view;
        Rectangle CompRect;

        static int f = 0;
        static Random rnd = new Random();
        static int size = 6;
        static int columnGrid = 99;
        Vector2 sizeVector = new Vector2(size);

        /// <summary>
        /// Initializes the singleton application object.  This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App()
        {
            this.InitializeComponent();
            this.UnhandledException += App_UnhandledException;
            this.Suspending += OnSuspending;
        }

        private void App_UnhandledException(object sender, Windows.UI.Xaml.UnhandledExceptionEventArgs e)
        {
            e.Handled = true;
        }

        /// <summary>
        /// Invoked when the application is launched normally by the end user.  Other entry points
        /// will be used such as when the application is launched to open a specific file.
        /// </summary>
        /// <param name="e">Details about the launch request and process.</param>
        protected override void OnLaunched(LaunchActivatedEventArgs e)
        {
            Grid rootFrame = Window.Current.Content as Grid;

            // Do not repeat app initialization when the Window already has content,
            // just ensure that the window is active
            if (rootFrame == null)
            {
                // Create a Frame to act as the navigation context and navigate to the first page
                rootFrame = new Grid();

                CompRect = new Rectangle();
                Button Draw = new Button() { Content = "Draw!", HorizontalAlignment = HorizontalAlignment.Center };
                rootFrame.Children.Add(CompRect);
                rootFrame.Children.Add(Draw);
                rootFrame.Loaded += RootFrame_Loaded;
                Draw.Click += Draw_Click;

                //rootFrame.NavigationFailed += OnNavigationFailed;

                if (e.PreviousExecutionState == ApplicationExecutionState.Terminated)
                {
                    //TODO: Load state from previously suspended application
                }

                // Place the frame in the current Window
                Window.Current.Content = rootFrame;
            }

            if (e.PrelaunchActivated == false)
            {
                if (rootFrame == null)
                {
                    // When the navigation stack isn't restored navigate to the first page,
                    // configuring the new page by passing required information as a navigation
                    // parameter
                    //rootFrame.Navigate(typeof(MainPage), e.Arguments);
                }
                // Ensure the current window is active
                Window.Current.Activate();
            }
        }

        private void RootFrame_Loaded(object sender, RoutedEventArgs e)
        {
            compositor = Window.Current.Compositor;
            visual = compositor.CreateContainerVisual();
            ElementCompositionPreview.SetElementChildVisual(CompRect, visual);
            view = ApplicationView.GetForCurrentView();
        }

        private async void Draw_Click(object sender, RoutedEventArgs e)
        {
            await Task.Run(() =>
            {
                visual.Children.RemoveAll();

                view.Title = "Creating visuals....";
                Stopwatch sp = Stopwatch.StartNew();
                for (int i = 0; i < columnGrid; i++)
                {
                    for (int j = 0; j < columnGrid + 1; j++) // 100 controls instead of 99
                    {
                        SpriteVisual b = compositor.CreateSpriteVisual();
                        b.Size = sizeVector;
                        //Random may slow down a bit, but it's for visual
                        //To test controls generation speed properly, please set a fixed color.
                        b.Brush = compositor.CreateColorBrush(Color.FromArgb(0xff, Convert.ToByte(rnd.Next(0, 256)), Convert.ToByte(rnd.Next(0, 256)), Convert.ToByte(rnd.Next(0, 256))));
                        b.Offset = new Vector3(i * size, j * size, 0);
                        visual.Children.InsertAtBottom(b);
                    }
                }

                sp.Stop();
                view.Title = "Visuals created in: " + sp.Elapsed.ToString("mm\\:ss\\.fff");
            });
        }

        /// <summary>
        /// Invoked when Navigation to a certain page fails
        /// </summary>
        /// <param name="sender">The Frame which failed navigation</param>
        /// <param name="e">Details about the navigation failure</param>
        void OnNavigationFailed(object sender, NavigationFailedEventArgs e)
        {
            throw new Exception("Failed to load Page " + e.SourcePageType.FullName);
        }

        /// <summary>
        /// Invoked when application execution is being suspended.  Application state is saved
        /// without knowing whether the application will be terminated or resumed with the contents
        /// of memory still intact.
        /// </summary>
        /// <param name="sender">The source of the suspend request.</param>
        /// <param name="e">Details about the suspend request.</param>
        private void OnSuspending(object sender, SuspendingEventArgs e)
        {
            var deferral = e.SuspendingOperation.GetDeferral();
            //TODO: Save application state and stop any background activity
            deferral.Complete();
        }
    }
}
