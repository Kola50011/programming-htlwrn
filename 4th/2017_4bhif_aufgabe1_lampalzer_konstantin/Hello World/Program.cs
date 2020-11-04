using System;

namespace Hello_World
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Console.WriteLine("Hello World");
            }
            else if (args.Length > 0)
            {
                string toPrint = "";
                for (int i = 0; i < args.Length; i++)
                    if (toPrint == "")
                    {
                        toPrint += args[i];
                    }
                    else
                    {
                        toPrint += " und " + args[i];
                        Console.WriteLine("Hallo " + toPrint);
                        toPrint = "";
                    }
                if (toPrint != "")
                    Console.WriteLine("Hallo " + toPrint);
            }
        }
    }
}