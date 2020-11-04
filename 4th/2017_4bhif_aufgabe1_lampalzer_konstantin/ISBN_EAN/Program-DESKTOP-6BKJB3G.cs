/*
 * Konstantin Lampalzer
 * 4BHIF
 * 21.9.17
 */

using System;
using Newtonsoft.Json;

namespace ISBN_EAN
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            Console.WriteLine(JsonConvert.SerializeObject(Isbn10.CheckIsbn("3-86680-192-0")));
            Console.WriteLine(JsonConvert.SerializeObject(Isbn13.CheckIsbn("978-1-56619-909-4")));
            Console.WriteLine(JsonConvert.SerializeObject(Ean13.CheckEan("5 449000 09624-1")));
        }
    }
}