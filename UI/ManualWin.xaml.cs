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
    /// ManualWin.xaml 的互動邏輯
    /// </summary>
    public partial class ManualWin : Window
    {
        internal void bdrWindowTitle_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            this.DragMove();
        }
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_MANUALALIGN = 1024 + 106;
        public ManualWin()
        {
            InitializeComponent();
        }

        private void ComboBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_MANUALALIGN, (IntPtr)0, (IntPtr)model_combo.SelectedIndex);
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

        private void Button_Event_Click(object sender, RoutedEventArgs e)
        {
            var btn = sender as Button;

            switch (btn.Name)
            {
                case "button_alignpoint_add":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_MANUALALIGN, (IntPtr)1, (IntPtr)0);
                    break;
                case "button_alignpoint_confirm":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_MANUALALIGN, (IntPtr)1, (IntPtr)1);
                    break;
                case "button_alignpoint_reset":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_MANUALALIGN, (IntPtr)1, (IntPtr)2);
                    break;
            }
        }
    }
}
