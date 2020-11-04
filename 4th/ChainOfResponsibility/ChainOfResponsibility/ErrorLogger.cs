using System;

namespace ChainOfResponsibility
{
    public class ErrorLogger : AbstractLogger
    {
        public ErrorLogger(LogLevel level, AbstractLogger nextLogger = null) : base(level, nextLogger)
        {
            Level = level;
            NextLogger = nextLogger;
        }

        public override void Write(string message)
        {
            Console.WriteLine($"!!!!!!!ERROR!!!!!!!! {message}");
        }
    }
}