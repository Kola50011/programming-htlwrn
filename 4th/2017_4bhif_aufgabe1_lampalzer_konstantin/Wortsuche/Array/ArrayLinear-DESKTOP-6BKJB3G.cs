﻿/*
 * Konstantin Lampalzer
 * 4BHIF
 * 21.9.17
 */

using System.Collections.Generic;
using System.IO;

namespace Wortsuche
{
    public class ArrayLinear : IWordList
    {
        public List<string> GetWordList(string word)
        {
            List<string> ret = new List<string>();

            string[] lines = File.ReadAllLines(@".\deutsch.txt");
            foreach (string line in lines)
                if (line.ToLower().StartsWith(word.ToLower()))
                    ret.Add(line);

            return ret;
        }

        public List<string> GetWordListEnding(string word)
        {
            List<string> ret = new List<string>();

            string[] lines = File.ReadAllLines(@".\deutsch.txt");
            foreach (string line in lines)
                if (line.ToLower().EndsWith(word.ToLower()))
                    ret.Add(line);

            return ret;
        }
    }
}