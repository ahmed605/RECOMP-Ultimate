using System;
using System.Diagnostics;
using System.Runtime.ExceptionServices;
using System.Runtime.InteropServices;
using System.Threading;
using Windows.System;
using WinRT;

namespace WUXIND
{
#if DISABLE_XAML_GENERATED_MAIN
    /// <summary>
    /// Program class
    /// </summary>
    public static class Program
    {
        [global::System.CodeDom.Compiler.GeneratedCodeAttribute("Microsoft.Windows.UI.Xaml.Build.Tasks", " 10.0.18362.1")]
        [global::System.Diagnostics.DebuggerNonUserCodeAttribute()]
        static void Main(string[] args)
        {
            try
            {
                Windows.UI.Xaml.Application.Start((p) =>
                {
                    new App();
                });
            }
            catch (Exception ex)
            {

            }
        }
    }
#endif
}