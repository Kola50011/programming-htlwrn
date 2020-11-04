/*
 * Konstantin Lampalzer
 * 4BHIF
 * 21.9.17
 */

using System;
using System.Collections.Generic;

namespace Roman
{
    public class Roman
    {
        private static readonly Dictionary<char, int> RomanMap = new Dictionary<char, int>
        {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000}
        };

        public static string IntToRoman(int number)
        {
            if (number < 0 || number > 3999) throw new ArgumentOutOfRangeException("insert value betwheen 1 and 3999");
            if (number < 1) return string.Empty;
            if (number >= 1000) return "M" + IntToRoman(number - 1000);
            if (number >= 900) return "CM" + IntToRoman(number - 900); //EDIT: i've typed 400 instead 900
            if (number >= 500) return "D" + IntToRoman(number - 500);
            if (number >= 400) return "CD" + IntToRoman(number - 400);
            if (number >= 100) return "C" + IntToRoman(number - 100);
            if (number >= 90) return "XC" + IntToRoman(number - 90);
            if (number >= 50) return "L" + IntToRoman(number - 50);
            if (number >= 40) return "XL" + IntToRoman(number - 40);
            if (number >= 10) return "X" + IntToRoman(number - 10);
            if (number >= 9) return "IX" + IntToRoman(number - 9);
            if (number >= 5) return "V" + IntToRoman(number - 5);
            if (number >= 4) return "IV" + IntToRoman(number - 4);
            if (number >= 1) return "I" + IntToRoman(number - 1);
            throw new ArgumentOutOfRangeException("ERROR");
        }

        public static int RomanToInt(string roman)
        {
            int number = 0;
            for (int i = 0; i < roman.Length; i++)
                if (i + 1 < roman.Length && RomanMap[roman[i]] < RomanMap[roman[i + 1]])
                    number -= RomanMap[roman[i]];
                else
                    number += RomanMap[roman[i]];
            return number;
        }
    }
}