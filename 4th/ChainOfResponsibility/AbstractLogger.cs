using System;

namespace ChainOfResponsibility
{
    public class AbstractLogger
    {
        public enum LogLevel
        {
            Info,
            Debug,
            Error
        }

        protected LogLevel Level;
        protected AbstractLogger NextLogger;

        public AbstractLogger(LogLevel level, AbstractLogger nextLogger = null)
        {
            Level = level;
            NextLogger = nextLogger;
        }

        public void Log(LogLevel level, string message)
        {
            if (level <= Level)
                Write(message);
            NextLogger?.Log(level, message);
        }

        private void Write(string message)
        {
            Console.WriteLine($"Level: {Level.ToString()} Message: {message}");
        }
    }
}