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
using System.Windows.Shapes;

namespace Thrift_Shop
{
    /// <summary>
    /// Interaction logic for AddProductWindow.xaml
    /// </summary>
    public partial class AddProductWindow : Window
    {
        public AddProductWindow()
        {
            InitializeComponent();
        }

        private void SubmitButton_Click(object sender, RoutedEventArgs e)
        {
            DB db = DB.Instance;
            if (Product.ValidPrice(PriceTextBox.GetLineText(0))) {
                Product product = new Product(
                    NameTextBox.GetLineText(0),
                    PriceTextBox.GetLineText(0),
                    CategoryTextBox.GetLineText(0),
                    BrandTextBox.GetLineText(0)
                    );
                product.AddToDB();
                Close();
            }
        }
    }
}
