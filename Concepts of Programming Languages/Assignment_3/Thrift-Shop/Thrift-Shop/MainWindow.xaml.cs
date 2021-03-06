﻿using System;
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

namespace Thrift_Shop
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            DB db = DB.Instance;
        }

        private void addProductButton_Click(object sender, RoutedEventArgs e)
        {
            AddProductWindow addProductWindow = new AddProductWindow();
            addProductWindow.Show();
        }

        private void ShowAllProductsButton_Click(object sender, RoutedEventArgs e)
        {
            AllProductsWindow allProductsWindow = new AllProductsWindow();
            allProductsWindow.Show();
        }

        private void ShowBrandsButton_Click(object sender, RoutedEventArgs e)
        {
            Windows.ShowBrandsWindow showBrandsWindow = new Windows.ShowBrandsWindow();
            showBrandsWindow.Show();
        }
    }
}
