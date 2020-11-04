using System;
using System.Diagnostics;
using CommandLine;
using CommandLine.Text;

namespace _2017_4bhif_aufgabe4_lampalzer_konstantin
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            // Init options and parse them
            CommandLineOptions options = new CommandLineOptions();
            if (!Parser.Default.ParseArguments(args, options))
            {
                Console.ReadLine();
                return;
            }
            // Cache the Prime calculation once
            ConcurrentPrimCalculatior.Check(10000, 100);

            const int tabLength = 17;

            Console.Write($"{"max Primzahl",tabLength}");
            Console.Write($"{"nr. Primzahlen",tabLength}");

            for (int i = 1; i <= options.MaxThreads; i++)
                Console.Write($"{i + " Threads",tabLength}");

            Console.Write("\n");
            for (int i = 100000; i <= options.MaxNumber; i += 100000)
            {
                Console.Write($"{i,tabLength}");

                // 1 Thread
                Stopwatch watch = new Stopwatch();
                watch.Start();
                int primeNumbers = ConcurrentPrimCalculatior.Check(i, 1);
                watch.Stop();

                // nr. Primzahlen
                Console.Write($"{primeNumbers,tabLength}");
                Console.Write($"{watch.ElapsedMilliseconds,tabLength}");

                // Extra threads
                for (int j = 2; j <= options.MaxThreads; j++)
                {
                    watch = new Stopwatch();
                    watch.Start();
                    ConcurrentPrimCalculatior.Check(i, j);
                    watch.Stop();
                    Console.Write($"{watch.ElapsedMilliseconds,tabLength}");
                }
                Console.Write("\n");
            }
            Console.ReadLine();
        }
    }

    internal class CommandLineOptions
    {
        [Option('t', "maxThreads", Required = true,
            HelpText = "Max amount of threads.")]
        public int MaxThreads { get; set; }

        [Option('n', "maxNumber", Required = true,
            HelpText = "Highest number to be checked for prime numbers.")]
        public int MaxNumber { get; set; }

        [ParserState]
        public IParserState LastParserState { get; set; }

        [HelpOption]
        public string GetUsage()
        {
            return HelpText.AutoBuild(this, current => HelpText.DefaultParsingErrorsHandler(this, current));
        }
    }
}