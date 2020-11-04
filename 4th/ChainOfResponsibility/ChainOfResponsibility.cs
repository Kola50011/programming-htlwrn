namespace ChainOfResponsibility
{
    public class ChainOfResponsibility
    {
        public static AbstractLogger CreateChain()
        {
            ErrorLogger errorLogger = new ErrorLogger(AbstractLogger.LogLevel.Error);
            DebugLogger debugLogger = new DebugLogger(AbstractLogger.LogLevel.Debug, errorLogger);
            InfoLogger infoLogger = new InfoLogger(AbstractLogger.LogLevel.Info, debugLogger);
            return infoLogger;
        }

        public static void Main(string[] args)
        {
            AbstractLogger logger = CreateChain();
            logger.Log(AbstractLogger.LogLevel.Debug, "Das ist eine Debugnachricht");
            logger.Log(AbstractLogger.LogLevel.Error,
                "ACHTUNG!!!! Es ist ein Fehler aufgetreten! Lanch the Cyber-nuke");
            logger.Log(AbstractLogger.LogLevel.Info, "Das ist eine infomative Informationsnachricht!");
        }
    }
}