using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace UI
{
    /// <summary>
    /// Interaction logic for SamplePage.xaml
    /// </summary>
    public partial class SamplePage : Page
    {
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_SAMPLEPAGE = 1024 + 101;

        private float test_value;
        public SamplePage()
        {
            InitializeComponent();

            test_value = 100;
        }

        public float GetTestValue()
        {
            return test_value;
        }
    }
}
