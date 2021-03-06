﻿using InterProcessCommunicator;
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
    /// ExtractWin.xaml 的互動邏輯
    /// </summary>
    public partial class ExtractWin : Window
    {
        internal void bdrWindowTitle_MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            this.DragMove();
        }
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_EXTRACT = 1024 + 107;

        public ExtractWin()
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

        private void Button_Event_Click(object sender, RoutedEventArgs e)
        {
            int radio_selected = -1;

            if (m_sinus.IsChecked == true)              radio_selected = 1;
            else if (m_airway.IsChecked == true)        radio_selected = 2;
            else if (m_root.IsChecked == true)          radio_selected = 3;
            else if (m_bone.IsChecked == true)          radio_selected = 4;

            if (radio_selected == -1) return;

            var btn = sender as Button;

            switch (btn.Name)
            {
                case "button_extract_add":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_EXTRACT, (IntPtr)0, (IntPtr)radio_selected);
                    break;
                case "button_extract_confirm":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_EXTRACT, (IntPtr)1, (IntPtr)radio_selected);
                    break;
                case "button_extract_reset":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_EXTRACT, (IntPtr)2, (IntPtr)radio_selected);
                    break;
            }
        }
    }
}
