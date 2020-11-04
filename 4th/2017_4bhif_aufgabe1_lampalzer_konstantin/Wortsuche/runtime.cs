using System;
using System.Diagnostics;

namespace Wortsuche
{
    public static class Runtime
    {
        public static void PrintRuntime()
        {
            int n = 10;
            double arrayLinear = GetArrayLinearTime(n);
            Console.WriteLine($"ArrayLinear took {arrayLinear}ms");

            double arrayBinary = GetArrayBinaryTime(n);
            Console.WriteLine($"ArrayBinary took {arrayBinary}ms");

            double collectionLinear = GetCollectionLinearTime(n);
            Console.WriteLine($"CollectionLinear took {collectionLinear}ms");

            double collectionBinary = GetCollectionBinaryTime(n);
            Console.WriteLine($"CollectionBinary took {collectionBinary}ms");

            double arraLinearEnding = GetArrayLinearEndingTime(n);
            Console.WriteLine($"ArraLinearEnding took {arraLinearEnding}ms");

            double collectionLinearEnding = GetCollectionLinearEndingTime(n);
            Console.WriteLine($"CollectionLinearEnding took {collectionLinearEnding}ms");
        }

        private static double GetArrayLinearTime(int n)
        {
            Stopwatch arrayLinear = new Stopwatch();
            arrayLinear.Start();
            for (int i = 0; i < n; i++)
            {
                new ArrayLinear().GetWordList("Distanz");
                new ArrayLinear().GetWordList("Erdbi");
                new ArrayLinear().GetWordList("Finanzind");
            }
            arrayLinear.Stop();

            return arrayLinear.ElapsedMilliseconds / n;
        }

        private static double GetArrayBinaryTime(int n)
        {
            Stopwatch arrayBinary = new Stopwatch();
            arrayBinary.Start();

            for (int i = 0; i < n; i++)
            {
                new ArrayBinary().GetWordList("Distanz");
                new ArrayBinary().GetWordList("Erdbi");
                new ArrayBinary().GetWordList("Finanzind");
            }
            arrayBinary.Stop();

            return arrayBinary.ElapsedMilliseconds / n;
        }

        private static double GetCollectionLinearTime(int n)
        {
            Stopwatch collectionLinear = new Stopwatch();
            collectionLinear.Start();
            for (int i = 0; i < n; i++)
            {
                new CollectionLinear().GetWordList("Distanz");
                new CollectionLinear().GetWordList("Erdbi");
                new CollectionLinear().GetWordList("Finanzind");
            }
            collectionLinear.Stop();

            return collectionLinear.ElapsedMilliseconds / n;
        }

        private static double GetCollectionBinaryTime(int n)
        {
            Stopwatch collectionBinary = new Stopwatch();
            collectionBinary.Start();
            for (int i = 0; i < n; i++)
            {
                new CollectionBinary().GetWordList("Distanz");
                new CollectionBinary().GetWordList("Erdbi");
                new CollectionBinary().GetWordList("Finanzind");
            }
            collectionBinary.Stop();

            return collectionBinary.ElapsedMilliseconds / n;
        }

        private static double GetArrayLinearEndingTime(int n)
        {
            Stopwatch arrayLinear = new Stopwatch();
            arrayLinear.Start();
            for (int i = 0; i < n; i++)
            {
                new ArrayLinear().GetWordListEnding("gulierung");
                new ArrayLinear().GetWordListEnding("dcomputer");
                new ArrayLinear().GetWordListEnding("chsdor");
            }
            arrayLinear.Stop();

            return arrayLinear.ElapsedMilliseconds / n;
        }

        private static double GetCollectionLinearEndingTime(int n)
        {
            Stopwatch collectionLinear = new Stopwatch();
            collectionLinear.Start();
            for (int i = 0; i < n; i++)
            {
                new CollectionLinear().GetWordListEnding("gulierung");
                new CollectionLinear().GetWordListEnding("dcomputer");
                new CollectionLinear().GetWordListEnding("chsdor");
            }
            collectionLinear.Stop();

            return collectionLinear.ElapsedMilliseconds / n;
        }
    }
}