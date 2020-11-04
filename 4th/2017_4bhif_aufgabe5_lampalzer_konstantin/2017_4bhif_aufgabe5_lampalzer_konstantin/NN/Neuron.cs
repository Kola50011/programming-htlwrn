using System.Collections.Generic;
using System.Linq;

namespace _2017_4bhif_aufgabe5_lampalzer_konstantin.NN
{
    public class Neuron
    {
        public Neuron()
        {
            InputSynapses = new List<Synapse>();
            OutputSynapses = new List<Synapse>();
            Bias = Network.GetRandom();
        }

        public Neuron(IEnumerable<Neuron> inputNeurons) : this()
        {
            foreach (Neuron inputNeuron in inputNeurons)
            {
                Synapse synapse = new Synapse(inputNeuron, this);
                inputNeuron.OutputSynapses.Add(synapse);
                InputSynapses.Add(synapse);
            }
        }

        public List<Synapse> InputSynapses { get; set; }
        public List<Synapse> OutputSynapses { get; set; }
        public double Bias { get; set; }
        public double BiasDelta { get; set; }
        public double Gradient { get; set; }
        public double Value { get; set; }

        public virtual double CalculateValue()
        {
            return Value = Sigmoid.Output(InputSynapses.Sum(a => a.Weight * a.InputNeuron.Value) + Bias);
        }

        public double CalculateError(double target)
        {
            return target - Value;
        }

        public double CalculateGradient(double? target = null)
        {
            if (target == null)
                return Gradient = OutputSynapses.Sum(a => a.OutputNeuron.Gradient * a.Weight) *
                                  Sigmoid.Derivative(Value);

            return Gradient = CalculateError(target.Value) * Sigmoid.Derivative(Value);
        }

        public void UpdateWeights(double learnRate, double momentum)
        {
            double prevDelta = BiasDelta;
            BiasDelta = learnRate * Gradient;
            Bias += BiasDelta + momentum * prevDelta;

            foreach (Synapse synapse in InputSynapses)
            {
                prevDelta = synapse.WeightDelta;
                synapse.WeightDelta = learnRate * Gradient * synapse.InputNeuron.Value;
                synapse.Weight += synapse.WeightDelta + momentum * prevDelta;
            }
        }
    }
}