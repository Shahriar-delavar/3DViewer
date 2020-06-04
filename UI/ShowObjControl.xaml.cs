using InterProcessCommunicator;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
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
    /// ShowObjControl.xaml 的互動邏輯
    /// </summary>
    public partial class ShowObjControl : Page
    {
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_SHOWSETTING = 1024 + 109;

        public enum EventName : int
        {
            SHOWDLG,
            HIDEDLG,
            VIEW_LEFT,
            VIEW_FRONT,
            VIEW_RIGHT,
            SHOW_3D,
            HIDE_3D,
            SHOW_INFOR,
            HIDE_INFOR,
            SHOW_GRID,
            HIDE_GRID,
            SHOW_COLORMAP,
            HIDE_COLORMAP,
            VOLUME_1,
            VOLUME_2,
            VOLUME_3,
            VOLUME_4,
            VOLUME_5,
            VOLUME_6,
            BUTTON_CT,
            BUTTON_UPPER,
            BUTTON_LOWER,
            BUTTON_CROWN,
            BUTTON_FACE
        }
        public ShowObjControl()
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

        private void ImgMouseEnter(object sender, MouseEventArgs e)
        {

        }

        private void ImgMouseLeave(object sender, MouseEventArgs e)
        {

        }

        private void ImageButton_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            if(sender is Image)
            {
                switch(((Image)sender).Name)
                {
                    case "ViewCT":
                        {
                            if (ScrollCT.Value == 100)
                                ScrollCT.Value = 0;
                            else if (ScrollCT.Value < 100 && ScrollCT.Value >= 50)
                                ScrollCT.Value = 100;
                            else
                                ScrollCT.Value = 50;
                            break;
                        }
                    case "ViewMaxilla":
                        {
                            if (ScrollMaxilla.Value == 100)
                                ScrollMaxilla.Value = 0;
                            else if (ScrollMaxilla.Value < 100 && ScrollMaxilla.Value >= 50)
                                ScrollMaxilla.Value = 100;
                            else
                                ScrollMaxilla.Value = 50;
                            break;
                        }
                    case "ViewMandible":
                        {
                            if (ScrollMandible.Value == 100)
                                ScrollMandible.Value = 0;
                            else if (ScrollMandible.Value < 100 && ScrollMandible.Value >= 50)
                                ScrollMandible.Value = 100;
                            else
                                ScrollMandible.Value = 50;
                            break;
                        }
                    case "ViewCrown":
                        {
                            if (ScrollCrown.Value == 100)
                                ScrollCrown.Value = 0;
                            else if (ScrollCrown.Value < 100 && ScrollCrown.Value >= 50)
                                ScrollCrown.Value = 100;
                            else
                                ScrollCrown.Value = 50;
                            break;
                        }
                    case "ViewFace":
                        {
                            if (ScrollFace.Value == 100)
                                ScrollFace.Value = 0;
                            else if (ScrollFace.Value < 100 && ScrollFace.Value >= 50)
                                ScrollFace.Value = 100;
                            else
                                ScrollFace.Value = 50;
                            break;
                        }
                }
            }
        }

        private void Slider_MouseWheel(object sender, MouseWheelEventArgs e)
        {

        }

        private void Scroll_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            var btn = sender as Slider;

            switch (btn.Name)
            {
                case "ScrollCT":
                    {
                        SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)5, (IntPtr)ScrollCT.Value);
                        break;
                    }
                case "ScrollMaxilla":
                    {
                        SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)6, (IntPtr)ScrollMaxilla.Value);
                        break;
                    }
                case "ScrollMandible":
                    {
                        SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)7, (IntPtr)ScrollMandible.Value);
                        break;
                    }
                case "ScrollCrown":
                    {
                        SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)8, (IntPtr)ScrollCrown.Value);
                        break;
                    }
                case "ScrollFace":
                    {
                        SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)9, (IntPtr)ScrollFace.Value);
                        break;
                    }
            }
        }

        private void ViewLeft_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)1, (IntPtr)EventName.VIEW_LEFT);
        }

        private void ViewISO_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)1, (IntPtr)EventName.VIEW_FRONT);
        }

        private void ViewRight_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {
            SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)1, (IntPtr)EventName.VIEW_RIGHT);
        }

        private void DimChk_Click(object sender, RoutedEventArgs e)
        {
            if (DimChk.IsChecked == false)
            {
                SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)2, (IntPtr)EventName.HIDE_3D);
            }
            else
            {
                SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)2, (IntPtr)EventName.SHOW_3D);
            }
        }
        private void Color_Click(object sender, RoutedEventArgs e)
        {
            if (ColormapChk.IsChecked == false)
            {
                SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)2, (IntPtr)EventName.HIDE_COLORMAP);
            }
            else
            {
                SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)2, (IntPtr)EventName.SHOW_COLORMAP);
            }
        }

        private void Grid_Click(object sender, RoutedEventArgs e)
        {
            if (GridChk.IsChecked == false)
            {
                SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)2, (IntPtr)EventName.HIDE_GRID);
            }
            else
            {
                SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)2, (IntPtr)EventName.SHOW_GRID);
            }
        }

        private void InforChk_Click(object sender, RoutedEventArgs e)
        {
            if (InforChk.IsChecked == false)
            {
                SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)2, (IntPtr)EventName.HIDE_INFOR);
            }
            else
            {
                SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)2, (IntPtr)EventName.SHOW_INFOR);
            }
        }

        private void Checked_volume(object sender, RoutedEventArgs e)
        {
            var btn = sender as ToggleButton;

            switch (btn.Name)
            {
                case "volume1":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)3, (IntPtr)EventName.VOLUME_1);
                    volume2.IsChecked = false;
                    volume3.IsChecked = false;
                    volume4.IsChecked = false;
                    volume5.IsChecked = false;
                    volume6.IsChecked = false;
                    break;
                case "volume2":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)3, (IntPtr)EventName.VOLUME_2);
                    volume1.IsChecked = false;
                    volume3.IsChecked = false;
                    volume4.IsChecked = false;
                    volume5.IsChecked = false;
                    volume6.IsChecked = false;
                    break;
                case "volume3":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)3, (IntPtr)EventName.VOLUME_3);
                    volume1.IsChecked = false;
                    volume2.IsChecked = false;
                    volume4.IsChecked = false;
                    volume5.IsChecked = false;
                    volume6.IsChecked = false;
                    break;
                case "volume4":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)3, (IntPtr)EventName.VOLUME_4);
                    volume1.IsChecked = false;
                    volume2.IsChecked = false;
                    volume3.IsChecked = false;
                    volume5.IsChecked = false;
                    volume6.IsChecked = false;
                    break;
                case "volume5":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)3, (IntPtr)EventName.VOLUME_5);
                    volume1.IsChecked = false;
                    volume2.IsChecked = false;
                    volume3.IsChecked = false;
                    volume4.IsChecked = false;
                    volume6.IsChecked = false;
                    break;
                case "volume6":
                    SendMessageClass.SendMessage(HostHandle, WM_WPFUI_SHOWSETTING, (IntPtr)3, (IntPtr)EventName.VOLUME_6);
                    volume1.IsChecked = false;
                    volume2.IsChecked = false;
                    volume3.IsChecked = false;
                    volume4.IsChecked = false;
                    volume5.IsChecked = false;
                    break;
            }
        }

        private void UnChecked_volume(object sender, RoutedEventArgs e)
        {

        }

        public void Togglebutton_uncheck()
        {
            volume2.IsChecked = false;
        }

    }
}
