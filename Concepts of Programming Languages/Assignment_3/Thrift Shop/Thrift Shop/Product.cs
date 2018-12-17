﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Thrift_Shop
{
    class Product
    {
        public string Name { get; set; }
        public double Price { get; set; }
        public string Category { get; set; }
        public string Brand { get; set; }

        public Product(string name, string price, string category, string brand)
        {
            if (!ValidPrice(price)) throw new Exception();
            Name = name;
            Price = double.Parse(price);
            Category = category;
            Brand = brand;
        }

        public void AddToDB()
        {
            DB.Instance.AddProduct(this);
        }

        public static bool ValidPrice(string price)
        {
            return double.TryParse(price, out double n);
        }
    }
}
