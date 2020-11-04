namespace _2017_4bhif_aufgabe5_lampalzer_konstantin.NN
{
    public class DataSet
    {
        public DataSet(double[] values, double[] targets)
        {
            Values = values;
            Targets = targets;
        }

        public double[] Values { get; set; }
        public double[] Targets { get; set; }
    }
}