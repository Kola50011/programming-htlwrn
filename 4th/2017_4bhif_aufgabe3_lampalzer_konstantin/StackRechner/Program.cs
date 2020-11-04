using System.Windows.Forms;

namespace StackRechner
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            StackRechner stackRechner = new StackRechner();
            Application.Run(new Rechner(stackRechner));
        }
    }
}