using System;
using System.Collections.Generic;
using System.Linq;

namespace _2017_4bhif_aufgabe5_lampalzer_konstantin.NN
{
    public class Network
    {
        private static readonly Random Random = new Random();

        public Network()
        {
            LearnRate = 0;
            Momentum = 0;
            InputLayer = new List<Neuron>();
            HiddenLayers = new List<List<Neuron>>();
            OutputLayer = new List<Neuron>();
        }

        public Network(int inputSize, int[] hiddenSizes, int outputSize, double learnRate = .4,
            double momentum = .9)
        {
            NumCalc = 0;
            Error = 0;
            Accuracy = 0;
            LearnRate = learnRate;
            Momentum = momentum;
            InputLayer = new List<Neuron>();
            HiddenLayers = new List<List<Neuron>>();
            OutputLayer = new List<Neuron>();

            for (int i = 0; i < inputSize; i++)
                InputLayer.Add(new Neuron());

            List<Neuron> firstHiddenLayer = new List<Neuron>();
            for (int i = 0; i < hiddenSizes[0]; i++)
                firstHiddenLayer.Add(new Neuron(InputLayer));

            HiddenLayers.Add(firstHiddenLayer);

            for (int i = 1; i < hiddenSizes.Length; i++)
            {
                List<Neuron> hiddenLayer = new List<Neuron>();
                for (int j = 0; j < hiddenSizes[i]; j++)
                    hiddenLayer.Add(new Neuron(HiddenLayers[i - 1]));
                HiddenLayers.Add(hiddenLayer);
            }

            for (int i = 0; i < outputSize; i++)
                OutputLayer.Add(new Neuron(HiddenLayers.Last()));
        }

        public double LearnRate { get; set; }
        public double Momentum { get; set; }
        public List<Neuron> InputLayer { get; set; }
        public List<List<Neuron>> HiddenLayers { get; set; }
        public List<Neuron> OutputLayer { get; set; }
        public double Error { get; set; }
        public int NumCalc { get; set; }
        public int Accuracy { get; set; }

        public void Train(List<DataSet> dataSets, int numEpochs)
        {
            for (int i = 0; i < numEpochs; i++)
                foreach (DataSet dataSet in dataSets)
                {
                    ForwardPropagate(dataSet.Values);
                    BackPropagate(dataSet.Targets);
                }
        }

        public void Train(List<DataSet> dataSets, double minimumError)
        {
            double error = 1.0;
            double numEpochs = 0;

            while (error > minimumError && numEpochs < int.MaxValue)
            {
                List<double> errors = new List<double>();
                foreach (DataSet dataSet in dataSets)
                {
                    ForwardPropagate(dataSet.Values);
                    BackPropagate(dataSet.Targets);
                    errors.Add(CalculateError(dataSet.Targets));
                }
                error = errors.Average();
                numEpochs++;
            }
        }

        private void ForwardPropagate(params double[] inputs)
        {
            int i = 0;
            InputLayer.ForEach(a => a.Value = inputs[i++]);
            HiddenLayers.ForEach(a => a.AsParallel().ForAll(b => b.CalculateValue()));
            OutputLayer.AsParallel().ForAll(a => a.CalculateValue());
        }

        private void BackPropagate(params double[] targets)
        {
            NumCalc++;

            int actual = targets.ToList().IndexOf(targets.Max());
            double[] outputs = OutputLayer.Select(a => a.Value).ToArray();
            int predicted = outputs.ToList().IndexOf(outputs.Max());

            if (actual == predicted)
            {
                Accuracy += 1;
            }

            int i = 0;
            OutputLayer.ForEach(a => a.CalculateGradient(targets[i++]));
            HiddenLayers.Reverse();
            HiddenLayers.ForEach(a => a.AsParallel().ForAll(b => b.CalculateGradient()));
            HiddenLayers.ForEach(a => a.AsParallel().ForAll(b => b.UpdateWeights(LearnRate, Momentum)));
            HiddenLayers.Reverse();
            OutputLayer.AsParallel().ForAll(a => a.UpdateWeights(LearnRate, Momentum));

            i = 0;
            double error = OutputLayer.Sum(a => Math.Abs(a.CalculateError(targets[i++])));
            Error += error;

            if (NumCalc % 1000 == 0)
            {
                Console.WriteLine($"Error: {Error / 1000 / 10} NumCalc: {NumCalc} Accuracy: {Accuracy / 10.0}");
                Error = 0;
                Accuracy = 0;
            }
        }

        public double[] Compute(params double[] inputs)
        {
            ForwardPropagate(inputs);
            return OutputLayer.Select(a => a.Value).ToArray();
        }

        private double CalculateError(params double[] targets)
        {
            int i = 0;
            return OutputLayer.Sum(a => Math.Abs(a.CalculateError(targets[i++])));
        }

        public static double GetRandom()
        {
            return 2 * Random.NextDouble() - 1;
        }
    }

    public enum TrainingType
    {
        Epoch,
        MinimumError
    }
}