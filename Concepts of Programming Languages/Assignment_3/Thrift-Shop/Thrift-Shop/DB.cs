using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Thrift_Shop
{
    sealed class DB
    {
        private static DB instance = new DB();

        private static readonly object padlock = new object();

        DB()
        {

        }

        public static DB Instance
        {
            get
            {
                lock (padlock)
                {
                    return instance;
                }
            }
        }

        private Model.thrift_shopEntities2 entities = new Model.thrift_shopEntities2();

        public void AddProduct(Product product)
        {
            var br = AddBrand(product.Brand);
            //entities.Database.Log = Console.Write;

            Model.product pr = new Model.product()
            {
                name = product.Name,
                category = product.Category,
                price = (float)product.Price,
                brand = br
            };

            entities.products.Add(pr);
            entities.SaveChanges();
        }

        private Model.brand AddBrand(string brand)
        {
            var q = from b in entities.brands
                    where b.name == brand
                    select b;
            if (q.Any())
                return q.First();

            Model.brand br = new Model.brand
            {
                name = brand
            };

            entities.brands.Add(br);
            entities.SaveChanges();
            return br;
        }

        public List<Model.product> GetAllProducts(double price = 1e9)
        {
            var query = from p in entities.products
                        join b in entities.brands on p.brand_id equals b.id
                        where p.price <= price
                        select p;
            return query.ToList();
        }

        public List<Brand> GetAllBrands()
        {
            var query = from b in entities.brands
                        let productCount = (
                            from p in entities.products
                            where p.brand_id == b.id
                            select p.id
                        ).Count()
                        orderby productCount descending
                        select new Brand()
                        {
                            Name = b.name,
                            ProductCount = productCount
                        };
            return query.ToList();
        }
    }
}
