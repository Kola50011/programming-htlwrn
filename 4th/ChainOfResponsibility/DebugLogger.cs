﻿using System;

namespace ChainOfResponsibility
{
    public class DebugLogger : AbstractLogger
    {
        public DebugLogger(LogLevel level, AbstractLogger nextLogger = null) : base(level, nextLogger)
        {
            Level = level;
            NextLogger = nextLogger;
        }

        private void Write(string message)
        {
            Console.WriteLine($"DEBUG: {message}");
        }
    }
}