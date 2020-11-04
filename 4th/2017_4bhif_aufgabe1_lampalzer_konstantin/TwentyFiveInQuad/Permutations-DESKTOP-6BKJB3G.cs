/*
 * Konstantin Lampalzer
 * 4BHIF
 * 21.9.17
 */

using System.Collections.Generic;

namespace TwentyFiveInQuad
{
    /// <summary>
    ///     Heap's Algorithm. See: https://en.wikipedia.org/wiki/Heap%27s_algorithm#cite_note-3
    /// </summary>
    public static class Permutations
    {
        public static List<int[]> Generate(int n, int[] a)
        {
            List<int[]> ret = new List<int[]>();
            int[] c = new int[n];

            for (int init = 0; init < n; init++)
                c[init] = 0;

            if (IsValid(a))
                ret.Add(a);

            int i = 0;
            while (i < n)
                if (c[i] < i)
                {
                    if (i % 2 == 0)
                    {
                        int temp = a[0];
                        a[0] = a[i];
                        a[i] = temp;
                    }
                    else
                    {
                        int temp = a[c[i]];
                        a[c[i]] = a[i];
                        a[i] = temp;
                    }

                    if (IsValid(a))
                        ret.Add(a);

                    c[i] += 1;
                    i = 0;
                }
                else
                {
                    c[i] = 0;
                    i += 1;
                }

            return ret;
        }

        public static bool IsValid(int[] z)
        {
            if (z[0] + z[1] + z[2] + z[3] != 25) return false;
            if (z[3] + z[4] + z[5] + z[6] != 25) return false;
            if (z[6] + z[7] + z[8] + z[9] != 25) return false;
            if (z[9] + z[10] + z[11] + z[1] != 25) return false;
            return true;
        }
    }
}