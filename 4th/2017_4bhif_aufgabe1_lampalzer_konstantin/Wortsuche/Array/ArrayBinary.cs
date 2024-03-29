﻿using System;
using System.Collections.Generic;
using System.IO;

namespace Wortsuche
{
    public class ArrayBinary : IWordList
    {
        public List<string> GetWordList(string word)
        {
            List<string> ret = new List<string>();

            string[] lines = File.ReadAllLines(@".\deutsch.txt");

            int pos = BinarySearchRecursive(lines, word, 0, lines.Length - 1);
            int i = pos;
            while (i >= 0 && i <= lines.Length - 1 && lines[i].ToLower().StartsWith(word.ToLower()))
            {
                ret.Add(lines[i]);
                i--;
            }

            i = pos + 1;
            while (i >= 0 && i <= lines.Length - 1 && lines[i].ToLower().StartsWith(word.ToLower()))
            {
                ret.Add(lines[i]);
                i++;
            }

            return ret;
        }

        public static int BinarySearchRecursive(string[] inputArray, string key, int min, int max)
        {
            if (min > max)
                return 0;
            int mid = (min + max) / 2;
            if (inputArray[mid].ToLower().StartsWith(key.ToLower()))
                return mid;
            if (String.CompareOrdinal(key.ToLower(), inputArray[mid].ToLower()) < 0)
                return BinarySearchRecursive(inputArray, key, min, mid - 1);
            return BinarySearchRecursive(inputArray, key, mid + 1, max);
        }
    }
}