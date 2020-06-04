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
using Microsoft.Win32;

namespace UI
{
    /// <summary>
    /// FileImport_3DFace.xaml 的互動邏輯
    /// </summary>
    public partial class FileImport_3DFace : Window
    {
        public string Selected_folder_path;
        internal void bdrWindowTitle_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            this.DragMove();
        }
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_FILEPROCESSWIN = 1024 + 103;

        public bool file_type_is_ok;
        public FileImport_3DFace()
        {
            InitializeComponent();

            Selected_folder_path = "c:\\Sample.obj";

            file_type_is_ok = false;

            m_model_path.Text = Selected_folder_path;

            //if (!Directory.Exists(Selected_folder_path))
            //{
            //    Directory.CreateDirectory(Selected_folder_path);
            //}
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
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.InitialDirectory = Selected_folder_path;
            dialog.Filter = "Model file (*.obj)|*.obj";
            if (dialog.ShowDialog() == true)
            {
                m_model_path.Text = dialog.FileName;
                Selected_folder_path = System.IO.Path.GetDirectoryName(dialog.FileName);
                Selected_folder_path = m_model_path.Text.ToString();
            }

            if (Selected_folder_path.IndexOf(".obj") == -1)
            {
                file_type_is_ok = false;
            }
            else
            {
                file_type_is_ok = true;
            }
        }
        private void Button_Event_Click(object sender, RoutedEventArgs e)
        {
            var btn = sender as Button;

            switch (btn.Name)
            {
                case "browmodel":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)50, (IntPtr)0);
                    break;
                case "BtnOpen":
                    if (file_type_is_ok) SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)50, (IntPtr)1);

                    break;
                case "BtnCancel":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_FILEPROCESSWIN, (IntPtr)50, (IntPtr)2);
                    break;
            }
        }
        public string GetCTFolderPath()
        {
            return m_model_path.Text.ToString();
        }
    }
}
