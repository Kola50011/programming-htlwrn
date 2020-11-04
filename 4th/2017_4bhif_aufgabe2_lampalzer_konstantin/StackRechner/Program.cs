using System;

namespace StackRechner
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            StackRechner rechner = new StackRechner();
            string input = Console.ReadLine();
            foreach (string s in input.Split(' '))
            {
                rechner.Push(s);
            }
            Console.ReadLine();
        }
    }
}