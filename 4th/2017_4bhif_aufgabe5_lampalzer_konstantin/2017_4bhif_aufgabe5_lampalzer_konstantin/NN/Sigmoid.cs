using System;

namespace _2017_4bhif_aufgabe5_lampalzer_konstantin.NN
{
    public static class Sigmoid
    {
        public static double Output(double x)
        {
            return x < -45.0 ? 0.0 : x > 45.0 ? 1.0 : 1.0 / (1.0 + Math.Exp(-x));
        }

        public static double Derivative(double x)
        {
            return x * (1 - x);
        }
    }
}