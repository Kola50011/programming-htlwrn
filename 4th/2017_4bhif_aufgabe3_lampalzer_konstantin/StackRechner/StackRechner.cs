using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace StackRechner
{
    public class StackRechner
    {
        public Stack<double> Stack = new Stack<double>();

        public void Push(string input)
        {
            double num;
            if (double.TryParse(input, out num))
            {
                Stack.Push(num);
                Console.WriteLine($@"{input,3} Push    {JsonConvert.SerializeObject(Stack)} ");
            }
            else
            {
                if (input == "sqr")
                {
                    double first = Stack.Pop();
                    Stack.Push(Math.Sqrt(first));
                }

                if (Stack.Count < 2)
                    return;
                switch (input)
                {
                    case "+":
                    {
                        Stack.Push(Stack.Pop() + Stack.Pop());
                        break;
                    }
                    case "-":
                    {
                        double first = Stack.Pop();
                        double second = Stack.Pop();
                        Stack.Push(second - first);
                        break;
                    }
                    case "*":
                    {
                        Stack.Push(Stack.Pop() * Stack.Pop());
                        break;
                    }
                    case "/":
                    {
                        double first = Stack.Pop();
                        double second = Stack.Pop();
                        Stack.Push(second / first);
                        break;
                    }
                    case "^":
                    {
                        double first = Stack.Pop();
                        double second = Stack.Pop();
                        Stack.Push(Math.Pow(second, first));
                        break;
                    }
                    case "e":
                    {
                        double first = Stack.Pop();
                        double second = Stack.Pop();
                        Stack.Push(second * Math.Pow(10, first));
                        break;
                    }
                }

                Console.WriteLine($@"{input,3} Operate {JsonConvert.SerializeObject(Stack)} ");
            }
        }
    }
}