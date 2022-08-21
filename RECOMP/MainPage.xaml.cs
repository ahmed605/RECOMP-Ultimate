using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Numerics;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
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

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace RECOMP
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        ContainerVisual visual;
        Compositor compositor;
        ApplicationView view;

        static int f = 0;
        static Random rnd = new Random();
        static int size = 6;
        static int columnGrid = 99;
        Vector2 sizeVector = new Vector2(size);

        public MainPage()
        {
            this.InitializeComponent();

            Init();
        }

        private void Init()
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
    }
}
