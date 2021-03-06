﻿using System;

namespace ChainOfResponsibility
{
    public class InfoLogger : AbstractLogger
    {
        public InfoLogger(LogLevel level, AbstractLogger nextLogger = null) : base(level, nextLogger)
        {
            Level = level;
            NextLogger = nextLogger;
        }

        private void Write(string message)
        {
            Console.WriteLine($"Level: {Level.ToString()} Message: {message}");
        }
    }
}