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
using System.Windows.Shapes;

namespace Thrift_Shop.Windows
{
    /// <summary>
    /// Interaction logic for ShowBrandsWindow.xaml
    /// </summary>
    public partial class ShowBrandsWindow : Window
    {
        public ShowBrandsWindow()
        {
            InitializeComponent();
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            System.Windows.Data.CollectionViewSource brandViewSource = ((System.Windows.Data.CollectionViewSource)(this.FindResource("brandViewSource")));
            // Load data by setting the CollectionViewSource.Source property:
            // brandViewSource.Source = [generic data source]
            brandViewSource.Source = DB.Instance.GetAllBrands();
        }
    }
}
