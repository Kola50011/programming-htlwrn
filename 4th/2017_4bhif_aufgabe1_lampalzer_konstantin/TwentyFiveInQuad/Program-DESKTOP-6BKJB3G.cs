/*
 * Konstantin Lampalzer
 * 4BHIF
 * 21.9.17
 */
 
 using System;
using System.Collections.Generic;

namespace TwentyFiveInQuad
{
    public class Program
    {
        private static void Main(string[] args)
        {
            List<int[]> validPerms = Permutations.Generate(12, new[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
            Console.WriteLine($"Valid Permutations: {validPerms.Count}");
            Console.ReadLine();
        }
    }
}