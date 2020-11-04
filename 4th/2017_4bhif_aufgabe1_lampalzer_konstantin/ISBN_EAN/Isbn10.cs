using System;

namespace ISBN_EAN
{
    public static class Isbn10
    {   
        private static string GetCheckDigit(string isbnWithoutCheckDigit)
        {
            int s = 0;
            for (int i = 1; i <= isbnWithoutCheckDigit.Length; i++)
            {
                int toAdd = int.Parse(isbnWithoutCheckDigit[i - 1] + "") * i;
                s += int.Parse(isbnWithoutCheckDigit[i - 1] + "") * i;
                Console.WriteLine("Digit Number: {0} Digit Value {1} Digit Sum {2}", i, isbnWithoutCheckDigit[i - 1],
                    toAdd);
            }
            int p = s % 11;
            if (p == 10)
                return "X";
            return p + "";
        }

        public static bool CheckIsbn(string isbn)
        {
            Console.WriteLine("Checking ISBN " + isbn);
            isbn = isbn.Replace(" ", "");
            isbn = isbn.Replace("-", "");
            string cd = GetCheckDigit(isbn.Remove(isbn.Length - 1));
            Console.WriteLine("ISBN Checknum " + cd);
            if (isbn.Length == 10)
                if (isbn[isbn.Length - 1] + "" == cd)
                    return true;
            return false;
        }
    }
}