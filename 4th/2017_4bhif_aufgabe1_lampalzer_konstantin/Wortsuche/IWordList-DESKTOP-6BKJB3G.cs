/*
 * Konstantin Lampalzer
 * 4BHIF
 * 21.9.17
 */
 
 using System.Collections.Generic;

namespace Wortsuche
{
    public interface IWordList
    {
        List<string> GetWordList(string word);
    }
}