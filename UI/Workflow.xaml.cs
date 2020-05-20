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
using InterProcessCommunicator;

namespace UI
{
    /// <summary>
    /// Workflow.xaml 的互動邏輯
    /// </summary>
    public partial class Workflow : Page
    {
        public IntPtr HostHandle { set; get; }
        BrushConverter bc = new BrushConverter();
        int NowProcess;
        bool P1_Checked, P2_1Checked, P2_2Checked, P3_Checked, P4_Checked, P5_Checked;

        private int WM_WPFUI_PROCESSBAR = 1024 + 102;

        public Workflow()
        {
            InitializeComponent();
            HostHandle = IntPtr.Zero;
            NowProcess = -1;
            P1_Checked = false;
            P2_1Checked = false;
            P2_2Checked = false;
            P3_Checked = false;
            P4_Checked = false;
            P5_Checked = false;
        }
        public double GetWidth()
        {
            double factor = System.Windows.PresentationSource.FromVisual(this).CompositionTarget.TransformToDevice.M11;
            return ((Grid)this.Content).RenderSize.Width * factor;
        }
        public double GetHeight()
        {
            double factor = System.Windows.PresentationSource.FromVisual(this).CompositionTarget.TransformToDevice.M11;
            return ((Grid)this.Content).RenderSize.Height * factor;
        }
        private void button1_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_PROCESSBAR, (IntPtr)1, (IntPtr)0);
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_PROCESSBAR, (IntPtr)2, (IntPtr)0);
        }

        private void button3_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_PROCESSBAR, (IntPtr)3, (IntPtr)0);
        }

        private void button4_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_PROCESSBAR, (IntPtr)4, (IntPtr)0);
        }

        private void button5_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_PROCESSBAR, (IntPtr)5, (IntPtr)0);
        }
    }
}
