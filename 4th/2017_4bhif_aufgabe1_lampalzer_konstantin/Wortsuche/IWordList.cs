using System.Collections.Generic;

namespace Wortsuche
{
    public interface IWordList
    {
        List<string> GetWordList(string word);
    }
}