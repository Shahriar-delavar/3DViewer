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
    /// FileProcessWin.xaml 的互動邏輯
    /// </summary>
    public partial class FileProcessWin : Window
    {
        internal void bdrWindowTitle_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            this.DragMove();
        }
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_FILEPROCESSWIN = 1024 + 103;

        public FileProcessWin()
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
                case "button_ct_load":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)0, (IntPtr)1);
                    break;
                case "button_ct_range":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)0, (IntPtr)2);
                    break;
                case "button_upper_load":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)1, (IntPtr)1);
                    break;
                case "button_upper_crown":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)1, (IntPtr)2);
                    break;
                case "button_upper_cut":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)1, (IntPtr)3);
                    break;
                case "button_lower_load":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)2, (IntPtr)1);
                    break;
                case "button_lower_crown":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)2, (IntPtr)2);
                    break;
                case "button_lower_cut":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)2, (IntPtr)3);
                    break;
                case "button_face_2d":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)3, (IntPtr)1);
                    break;
                case "button_face_3d":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)3, (IntPtr)2);
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
