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
    /// ShowObjControl.xaml 的互動邏輯
    /// </summary>
    public partial class ShowObjControl : Page
    {
        public IntPtr HostHandle { set; get; }

        private int WM_WPFUI_INFOSETTING = 1024 + 108;
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
        private void DimChk_Click(object sender, RoutedEventArgs e)
        {
            if (DimChk.IsChecked == false)
            {
                //dimImg.Source =;
            }
        }

        private void ImgMouseEnter(object sender, MouseEventArgs e)
        {

        }

        private void ImgMouseLeave(object sender, MouseEventArgs e)
        {

        }

        private void ImageButton_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {

        }

        private void Slider_MouseWheel(object sender, MouseWheelEventArgs e)
        {

        }

        private void Scroll_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

        }

        private void ViewLeft_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {

        }

        private void ViewISO_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {

        }

        private void ViewRight_MouseLeftButtonUp(object sender, MouseButtonEventArgs e)
        {

        }
    }
}
