/*
 * Konstantin Lampalzer
 * 4BHIF
 * 21.9.17
 */

using System;
using System.Collections.Generic;
using System.Diagnostics;

namespace Wortsuche
{
    public static class Runtime
    {
        public static void PrintRuntime()
        {
            PrintStart("Distanz");
            PrintStart("Erdbi");
            PrintStart("Finanzind");
            PrintEnd("gulierung");
            PrintEnd("dcomputer");
            PrintEnd("chsdor");
        }

        private static void PrintStart(string word)
        {
            Console.WriteLine($"-------- {word} --------");
            Stopwatch watch = new Stopwatch();

            watch.Start();
            List<string> wordList = new ArrayLinear().GetWordList(word);
            watch.Stop();
            long al = watch.ElapsedMilliseconds;
            Console.WriteLine($"Array Linear | {al,4}ms | {wordList.Count}");
            watch.Reset();

            watch.Start();
            wordList = new ArrayBinary().GetWordList(word);
            watch.Stop();
            long ab = watch.ElapsedMilliseconds;
            Console.WriteLine($"Array Binary | {ab,4}ms | {wordList.Count}");
            watch.Reset();

            watch.Start();
            wordList = new CollectionLinear().GetWordList(word);
            watch.Stop();
            long cl = watch.ElapsedMilliseconds;
            Console.WriteLine($"Coll. Linear | {cl,4}ms | {wordList.Count}");
            watch.Reset();

            watch.Start();
            wordList = new CollectionBinary().GetWordList(word);
            watch.Stop();
            long cb = watch.ElapsedMilliseconds;
            Console.WriteLine($"Coll. Binary | {cb,4}ms | {wordList.Count}");

            Console.WriteLine($"Linear       | {(al + cl) / 2,4} avg.");
            Console.WriteLine($"Binary       | {(ab + cb) / 2,4} avg.");
            Console.WriteLine($"Arrays       | {(al + ab) / 2,4} avg.");
            Console.WriteLine($"Collections  | {(cl + cb) / 2,4} avg.");
            Console.WriteLine();
        }

        private static void PrintEnd(string word)
        {
            Console.WriteLine($"-------- {word} --------");
            Stopwatch watch = new Stopwatch();

            watch.Start();
            List<string> wordList = new ArrayLinear().GetWordListEnding(word);
            watch.Stop();
            long al = watch.ElapsedMilliseconds;
            Console.WriteLine($"Array Linear | {al,4}ms | {wordList.Count}");
            watch.Reset();

            watch.Start();
            wordList = new CollectionLinear().GetWordListEnding(word);
            watch.Stop();
            long cl = watch.ElapsedMilliseconds;
            Console.WriteLine($"Coll. Linear | {cl,4}ms | {wordList.Count}");
            Console.WriteLine();
        }
    }
}