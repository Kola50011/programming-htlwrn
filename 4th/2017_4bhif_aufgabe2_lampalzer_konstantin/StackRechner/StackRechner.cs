using System;
using System.Collections.Generic;
using Newtonsoft.Json;

namespace StackRechner
{
    public class StackRechner
    {
        private readonly Stack<double> _stack = new Stack<double>();

        public void Push(string input)
        {
            int num;
            if (int.TryParse(input, out num))
            {
                _stack.Push(num);
                Console.WriteLine($"{input,3} Push    {JsonConvert.SerializeObject(_stack)} ");
            }
            else
            {
                switch (input)
                {
                    case "+":
                    {
                        _stack.Push(_stack.Pop() + _stack.Pop());
                        break;
                    }
                    case "-":
                    {
                        double first = _stack.Pop();
                        double second = _stack.Pop();
                        _stack.Push(second - first);
                        break;
                    }
                    case "*":
                    {
                        _stack.Push(_stack.Pop() * _stack.Pop());
                        break;
                    }
                    case "/":
                    {
                        double first = _stack.Pop();
                        double second = _stack.Pop();
                        _stack.Push(second / first);
                        break;
                    }
                    case "^":
                    {
                        double first = _stack.Pop();
                        double second = _stack.Pop();
                        _stack.Push(Math.Pow(second, first));
                        break;
                    }
                }
                Console.WriteLine($"{input,3} Operate {JsonConvert.SerializeObject(_stack)} ");
            }
        }
    }
}