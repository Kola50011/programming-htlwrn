using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;

namespace Wortsuche
{
    public class CollectionLinear : IWordList
    {
        public List<string> GetWordList(string word)
        {
            List<string> ret = new List<string>();

            Collection<string> lines = new Collection<string>(File.ReadAllLines(@".\deutsch.txt"));
            foreach (string line in lines)
                if (line.ToLower().StartsWith(word.ToLower()))
                    ret.Add(line);

            return ret;
        }

        public List<string> GetWordListEnding(string word)
        {
            List<string> ret = new List<string>();

            Collection<string> lines = new Collection<string>(File.ReadAllLines(@".\deutsch.txt"));
            foreach (string line in lines)
                if (line.ToLower().EndsWith(word.ToLower()))
                    ret.Add(line);

            return ret;
        }
    }
}