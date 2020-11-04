using System;
using System.IO;
using System.Threading.Tasks;
using System.Windows.Media.Imaging;

namespace _2017_4bhif_aufgabe6_lampalzer_konstantin
{
    public class ImageRotator
    {
        public ImageRotator(string inputDir, string outputDir,
            bool flipHorizontal = false, bool flipVertical = false,
            Rotation rot = Rotation.Rotate0, int quality = 100)
        {
            Progress = 0;
            Process(inputDir, outputDir, flipHorizontal, flipVertical, rot, quality);
        }

        private double Progress { get; set; }

        private void Process(string inputDir, string outputDir,
            bool flipHorizontal, bool flipVertical,
            Rotation rot, int quality)
        {
            string[] inputFiles = Directory.GetFiles(inputDir);
            double toAdd = 100 / inputFiles.Length;

            Parallel.ForEach(inputFiles, inputFile =>
            {
                FileStream stream = new FileStream($@"{outputDir} \ {Path.GetFileName(inputFile)}", FileMode.Create);
                JpegBitmapEncoder encoder = new JpegBitmapEncoder();
                encoder.FlipHorizontal = flipHorizontal;
                encoder.FlipVertical = flipVertical;
                encoder.QualityLevel = quality;
                encoder.Rotation = rot;
                encoder.Frames.Add(BitmapFrame.Create(new Uri(inputFile,
                    UriKind.Relative)));
                encoder.Save(stream);
                stream.Close();
                Progress += toAdd;
            });
        }
    }
}