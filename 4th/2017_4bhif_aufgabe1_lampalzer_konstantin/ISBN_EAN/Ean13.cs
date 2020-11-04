namespace ISBN_EAN
{
    public class Ean13
    {
        public static bool CheckEan(string ean)
        {
            ean = ean.Replace(" ", "");
            ean = ean.Replace("-", "");
            if (ean.Length != 13)
                return false;

            string z = ean;
            if (0 == (z[0] + z[2] + z[4] + z[6] + z[8] + z[10] + z[12] +
                      3 * (z[1] + z[3] + z[5] + z[7] + z[9] + z[11])) % 10)
                return true;
            return false;
        }
    }
}