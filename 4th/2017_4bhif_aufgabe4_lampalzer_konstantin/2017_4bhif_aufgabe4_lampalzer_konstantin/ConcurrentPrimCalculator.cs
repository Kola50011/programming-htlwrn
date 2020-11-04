using System;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace _2017_4bhif_aufgabe4_lampalzer_konstantin
{
    public static class ConcurrentPrimCalculatior
    {
        public static int Check(int maxToCheck, int maxParralell)
        {
            bool[] validPrims = new bool[maxToCheck + 1];

            uint lastToRemove = (uint) Math.Sqrt(maxToCheck);

            // Remove everything before lastToRemove Single-Threaded
            uint currentPrim = 2;
            while (currentPrim <= lastToRemove)
            {
                for (uint i = 2; currentPrim * i <= lastToRemove; i++)
                {
                    validPrims[currentPrim * i] = true;
                    i += 1;
                }

                // find next prim to remove
                currentPrim += 1;
                while (validPrims[currentPrim])
                    currentPrim += 1;
            }

            List<uint> primsBeforeLastToCheck = new List<uint>();
            for (uint i = 0; i < lastToRemove; i++)
                if (validPrims[i])
                    primsBeforeLastToCheck.Add(i);

            // Now remove mutiples of 0 - lastToRemove
            ParallelOptions options = new ParallelOptions {MaxDegreeOfParallelism = maxParralell};
            Parallel.ForEach(primsBeforeLastToCheck, options, toCheck =>
            {
                if (toCheck == 2)
                    for (uint i = 2; toCheck * i <= maxToCheck; i++)
                        validPrims[toCheck * i] = true;
                else
                    for (uint i = 3; toCheck * i <= maxToCheck; i += 2)
                        validPrims[toCheck * i] = true;
            });

            int count = 0;
            foreach (bool b in validPrims)
                if (!b)
                    count += 1;

            return count;
        }
    }
}