using InterProcessCommunicator;
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
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace UI
{
    /// <summary>
    /// AlignWin.xaml 的互動邏輯
    /// </summary>
    public partial class AlignWin : Window
    {
        internal void bdrWindowTitle_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            this.DragMove();
        }
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_ALIGN = 1024 + 105;
        public AlignWin()
        {
            InitializeComponent();
        }

        public double GetWidth()
        {
            return ((Grid)this.Content).RenderSize.Width;
        }
        public double GetHeight()
        {
            return ((Grid)this.Content).RenderSize.Height;
        }
        public void SetFramePosition(int MFCFrameTop, int MFCFrameLeft)
        {
            this.Top = MFCFrameTop - 20;
            this.Left = MFCFrameLeft + 20;
        }

        public void SetParentHwnd(IntPtr Parent)
        {
            HostHandle = Parent;
            WindowInteropHelper helper = new WindowInteropHelper(this);
            helper.Owner = Parent;
        }
        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void ComboBox_SelectionChanged_1(object sender, SelectionChangedEventArgs e)
        {

        }
        private void Button_Event_Click(object sender, RoutedEventArgs e)
        {
            var btn = sender as Button;

            switch (btn.Name)
            {
                case "button_alignpoint_add":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_ALIGN, (IntPtr)2, (IntPtr)0);
                    break;
                case "button_alignpoint_confirm":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_ALIGN, (IntPtr)2, (IntPtr)1);
                    break;
                case "button_alignpoint_reset":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_ALIGN, (IntPtr)2, (IntPtr)2);
                    break;
            }
        }
    }
}
