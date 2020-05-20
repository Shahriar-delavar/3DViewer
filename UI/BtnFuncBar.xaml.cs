using InterProcessCommunicator;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
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
    /// Interaction logic for BtnFuncBar.xaml
    /// </summary>
    public partial class BtnFuncBar : Page
    {
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_BTNFUNCBAR = 1024 + 100;
        private int WM_WPFUI_TEST = 1024 + 101;

        public BtnFuncBar()
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

        private void button1_Click(object sender, RoutedEventArgs e)
        {
            //MessageBox.Show("1");
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)0, (IntPtr)0);
        }

        private void button2_Click(object sender, RoutedEventArgs e)
        {
            //MessageBox.Show("2");
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)1, (IntPtr)0);
        }

        private void button3_Click(object sender, RoutedEventArgs e)
        {
            //MessageBox.Show("3");
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)2, (IntPtr)0);
        }

        private void button4_Click(object sender, RoutedEventArgs e)
        {
            //MessageBox.Show("4");
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)3, (IntPtr)0);
        }

        private void button5_Click(object sender, RoutedEventArgs e)
        {
            //MessageBox.Show("5");
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)4, (IntPtr)0);
        }

        private void button6_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)5, (IntPtr)0);
        }

        private void button7_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)6, (IntPtr)0);
        }

        private void button8_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)7, (IntPtr)0);
        }

        private void button9_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)8, (IntPtr)0);
        }

        private void button10_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)9, (IntPtr)0);
        }

        private void button11_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)10, (IntPtr)0);
        }

        private void button12_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)11, (IntPtr)0);
        }

        private void button13_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)12, (IntPtr)0);
        }

        private void button14_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)13, (IntPtr)0);
        }

        private void button15_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)14, (IntPtr)0);
        }

        private void button16_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)15, (IntPtr)0);
        }

        private void button17_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)16, (IntPtr)0);
        }

        private void button18_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)17, (IntPtr)0);
        }

        private void button19_Click(object sender, RoutedEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)18, (IntPtr)0);
        }

        private void button20_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("20");
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_BTNFUNCBAR, (IntPtr)19, (IntPtr)0);
        }

        private void button21_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show("21");
        }

        private void Maximize_Click(object sender, RoutedEventArgs e)
        {
            //this.WindowState = (this.WindowState == WindowState.Normal) ? WindowState.Maximized : WindowState.Normal;
        }

        private void Mimimize_Click(object sender, RoutedEventArgs e)
        {
            //this.WindowState = WindowState.Minimized;
        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            //Environment.Exit(0);
        }

        private void btnContactInteare_Click(object sender, RoutedEventArgs e)
        {

        }
    }
}
