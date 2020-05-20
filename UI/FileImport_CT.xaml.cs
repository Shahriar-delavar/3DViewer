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
using System.IO;

namespace UI
{
    /// <summary>
    /// FileImport_CT.xaml 的互動邏輯
    /// </summary>
    public partial class FileImport_CT : Window
    {

        public string Selected_folder_path;
        internal void bdrWindowTitle_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            this.DragMove();
        }
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_FILEPROCESSWIN = 1024 + 103;
        public FileImport_CT()
        {
            InitializeComponent();
            //if (Selected_folder_path == "")
            {
                Selected_folder_path = "c:\\DicomData";
            }

            m_ct_path.Text = Selected_folder_path;

            if (!Directory.Exists(Selected_folder_path))
            {
                Directory.CreateDirectory(Selected_folder_path);
            }
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

        private void Browse_Click(object sender, RoutedEventArgs e)
        {
            System.Windows.Forms.FolderBrowserDialog folderDialog = new System.Windows.Forms.FolderBrowserDialog();
            //Selected_folder_path = "c:\\DicomData";
            folderDialog.SelectedPath = Selected_folder_path;

            System.Windows.Forms.DialogResult result = folderDialog.ShowDialog();

            if (result == System.Windows.Forms.DialogResult.Cancel)
            {

            }
            else
            {
                m_ct_path.Text = folderDialog.SelectedPath.Trim();
            }
        }

        private void BtnOpen_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)10, (IntPtr)1);
            Selected_folder_path = m_ct_path.Text;
        }

        private void BtnCancel_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)10, (IntPtr)2);
        }

        private void Button_Event_Click(object sender, RoutedEventArgs e)
        {
            var btn = sender as Button;

            switch (btn.Name)
            {
                case "browct":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)10, (IntPtr)0);
                    break;
                case "BtnOpen":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)10, (IntPtr)1);
                    break;
                case "BtnCancel":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)10, (IntPtr)2);
                    break;
            }
        }
        public string GetCTFolderPath()
        {
            return m_ct_path.Text.ToString();
        }
    }
}
