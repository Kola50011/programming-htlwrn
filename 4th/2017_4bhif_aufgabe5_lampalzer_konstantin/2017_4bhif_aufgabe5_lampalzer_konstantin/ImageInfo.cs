namespace _2017_4bhif_aufgabe5_lampalzer_konstantin
{
    public class ImageInfo
    {
        public int Height;
        public double Label;
        public byte[][] Pixels;
        public int Width;

        public ImageInfo(byte[][] pixels,
            double label)
        {
            Pixels = pixels;
            Label = label;

            Width = pixels.Length;
            Height = pixels[0].Length;
        }

        public override string ToString()
        {
            string s = "";
            for (int i = 0; i < 28; ++i)
            {
                for (int j = 0; j < 28; ++j)
                    if (Pixels[i][j] == 0)
                        s += " "; // white
                    else if (Pixels[i][j] == 255)
                        s += "O"; // black
                    else
                        s += "."; // gray
                s += "\n";
            }
            s += Label.ToString();
            return s;
        }

        public double[] GetOneHot()
        {
            double[] ret = new double[Width * Height];
            int i = 0;
            for (int x = 0; x < Width; ++x)
            for (int y = 0; y < Height; ++y)
            {
                ret[i] = Pixels[x][y];
                i++;
            }
            return ret;
        }

        public double[] GetLableOneHot()
        {
            double[] ret = new double[10];
            for (int i = 0; i < 10; i++)
                ret[i] = 0;

            ret[(int) Label] = 1;
            return ret;
        }
    }
}