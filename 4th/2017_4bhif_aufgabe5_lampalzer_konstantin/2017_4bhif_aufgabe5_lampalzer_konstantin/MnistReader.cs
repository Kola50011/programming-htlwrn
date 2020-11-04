using System.Collections.Generic;
using System.IO;

namespace _2017_4bhif_aufgabe5_lampalzer_konstantin
{
    public static class MnistReader
    {
        public static List<ImageInfo> GetDataset(string labelFile, string imageFile, int width, int height, int count)
        {
            List<ImageInfo> dataSet = new List<ImageInfo>();

            // Read the files
            FileStream ifsLabels =
                new FileStream(labelFile,
                    FileMode.Open); // labels
            FileStream ifsImages =
                new FileStream(imageFile,
                    FileMode.Open); // images

            BinaryReader brLabels =
                new BinaryReader(ifsLabels);
            BinaryReader brImages =
                new BinaryReader(ifsImages);

            // Setup variables for the file format
            int magic1 = brImages.ReadInt32(); // discard
            int numImages = brImages.ReadInt32();
            int numRows = brImages.ReadInt32();
            int numCols = brImages.ReadInt32();

            int magic2 = brLabels.ReadInt32();
            int numLabels = brLabels.ReadInt32();

            // For image count images
            for (int anz = 0; anz < count; ++anz)
            {
                // Ready array where information gets stored
                byte[][] pixels = new byte[width][];
                for (int i = 0; i < pixels.Length; ++i)
                    pixels[i] = new byte[height];

                // Get the color value
                for (int x = 0; x < width; ++x)
                for (int y = 0; y < height; ++y)
                {
                    byte color = brImages.ReadByte();
                    pixels[x][y] = color;
                }

                // Get the label ( num between 0 - 9 )
                byte label = brLabels.ReadByte();

                ImageInfo dImageInfo =
                    new ImageInfo(pixels, label);

                dataSet.Add(dImageInfo);
            }

            ifsImages.Close();
            brImages.Close();
            ifsLabels.Close();
            brLabels.Close();

            return dataSet;
        }
    }
}