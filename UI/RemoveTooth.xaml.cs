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
    /// RemoveTooth.xaml 的互動邏輯
    /// </summary>
    ///
    public partial class RemoveTooth : Window
    {
        internal void bdrWindowTitle_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            this.DragMove();
        }
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_REMOVETOOTH = 1024 + 104;
        public RemoveTooth()
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

        private void Button_Event_Click(object sender, RoutedEventArgs e)
        {
            var btn = sender as Button;

            switch (btn.Name)
            {
                case "button_removeteeth_add":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_REMOVETOOTH, (IntPtr)0, (IntPtr)0);
                    break;
                case "button_removeteeth_delete":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_REMOVETOOTH, (IntPtr)1, (IntPtr)0);
                    break;
                case "button_removeteeth_reset":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_REMOVETOOTH, (IntPtr)2, (IntPtr)0);
                    break;
            }
        }

        public void SetParentHwnd(IntPtr Parent)
        {
            HostHandle = Parent;
            WindowInteropHelper helper = new WindowInteropHelper(this);
            helper.Owner = Parent;
        }

        public void SetPosition(int x, int y)
        {
            //this.Top = x;
            //this.Left = y;

        }
    }
}
