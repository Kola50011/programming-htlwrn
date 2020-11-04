/*
 * Konstantin Lampalzer
 * 4BHIF
 * 21.9.17
 */
 
 using Microsoft.VisualStudio.TestTools.UnitTesting;
using Wortsuche;

namespace WortsucheTest
{
    [TestClass]
    public class WortsucheTest
    {
        [TestMethod]
        public void Test()
        {
            CollectionAssert.AreEqual(new ArrayLinear().GetWordList("Distanz"), new ArrayBinary().GetWordList("Distanz"));
            CollectionAssert.AreEqual(new ArrayLinear().GetWordList("Distanz"), new CollectionLinear().GetWordList("Distanz"));
            CollectionAssert.AreEqual(new ArrayLinear().GetWordList("Distanz"), new CollectionBinary().GetWordList("Distanz"));

            CollectionAssert.AreEqual(new ArrayBinary().GetWordList("Distanz"), new CollectionBinary().GetWordList("Distanz"));

            CollectionAssert.AreEqual(new CollectionLinear().GetWordList("Distanz"), new ArrayBinary().GetWordList("Distanz"));
            CollectionAssert.AreEqual(new CollectionLinear().GetWordList("Distanz"), new CollectionBinary().GetWordList("Distanz"));
        }
    }
}