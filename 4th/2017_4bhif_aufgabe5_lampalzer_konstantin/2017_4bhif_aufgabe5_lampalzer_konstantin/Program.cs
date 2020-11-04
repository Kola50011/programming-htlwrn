using System;
using System.Collections.Generic;
using _2017_4bhif_aufgabe5_lampalzer_konstantin.NN;

namespace _2017_4bhif_aufgabe5_lampalzer_konstantin
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            List<ImageInfo> trainingsSetMnist = MnistReader.GetDataset(
                @"C:\Users\Koka\Google Drive\schule\4. Klasse\POS\2017_4bhif_aufgabe5_lampalzer_konstantin\TrainingsTestDaten\train-labels.idx1-ubyte",
                @"C:\Users\Koka\Google Drive\schule\4. Klasse\POS\2017_4bhif_aufgabe5_lampalzer_konstantin\TrainingsTestDaten\train-images.idx3-ubyte",
                28, 28, 60000);

            List<ImageInfo> testSetMnist = MnistReader.GetDataset(
                @"C:\Users\Koka\Google Drive\schule\4. Klasse\POS\2017_4bhif_aufgabe5_lampalzer_konstantin\TrainingsTestDaten\t10k-labels.idx1-ubyte",
                @"C:\Users\Koka\Google Drive\schule\4. Klasse\POS\2017_4bhif_aufgabe5_lampalzer_konstantin\TrainingsTestDaten\t10k-images.idx3-ubyte",
                28, 28, 10000);

            // convert mnistSets into actual DataSets
            List<DataSet> trainingsSet = new List<DataSet>();
            trainingsSetMnist.ForEach(imageInfo =>
                trainingsSet.Add(new DataSet(imageInfo.GetOneHot(), imageInfo.GetLableOneHot())));

            List<DataSet> testSet = new List<DataSet>();
            testSetMnist.ForEach(imageInfo =>
                testSet.Add(new DataSet(imageInfo.GetOneHot(), imageInfo.GetLableOneHot())));

            // Input layer with 28 x 28

            // nodes learn momentum epochs error
            // 100 .01 .01 2 0.076
            // 100,100,100 .01 .01 2 0.065

            Network network = new Network(28 * 28, new[] {100, 100, 100}, 10, .01, .01);
            network.Train(trainingsSet, 5);
            Console.ReadLine();
        }
    }
}