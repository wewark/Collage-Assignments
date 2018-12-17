using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SQLite;

namespace Thrift_Shop
{
    sealed class DB
    {
        private static DB instance = new DB();

        private static readonly object padlock = new object();

        DB()
        {
            //SQLiteConnection.CreateFile("db/my_db.db");
            con = new SQLiteConnection("Data Source=db/my_db.db;Version=3");
            con.Open();
            //CreateTables();
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

        private SQLiteConnection con;

        public void CreateTables()
        {
            string sql = @"
CREATE TABLE product (
`id` INT NOT NULL PRIMARY KEY,
name VARCHAR NOT NULL,
price FLOAT ,
category VARCHAR ,
brand_id INT ,
FOREIGN KEY (brand_id) REFERENCES brand(id)
);

CREATE TABLE brand (
`id` INT NOT NULL PRIMARY KEY,
name VARCHAR NOT NULL
);
";
            ExecuteNonQuery(sql);
        }

        private void ExecuteNonQuery(string sql)
        {
            SQLiteCommand command = new SQLiteCommand(sql, con);
            command.ExecuteNonQuery();
        }
    }
}
