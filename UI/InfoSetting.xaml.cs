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
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace UI
{
    /// <summary>
    /// InfoSetting.xaml 的互動邏輯
    /// </summary>
    public partial class InfoSetting : Page
    {
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_INFOSETTING = 1024 + 108;
        public InfoSetting()
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
        private void Button_Event_Click(object sender, RoutedEventArgs e)
        {
            var btn = sender as Button;

            switch (btn.Name)
            {
                case "button_patient_infor":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_INFOSETTING, (IntPtr)0, (IntPtr)1);
                    break;
                case "button_setting":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_INFOSETTING, (IntPtr)0, (IntPtr)2);
                    break;
            }
        }
    }
}
