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
            Assert.AreEqual(new ArrayLinear().GetWordList("Auto"), new ArrayBinary().GetWordList("Auto"));
            Assert.AreEqual(new ArrayLinear().GetWordList("Auto"), new CollectionLinear().GetWordList("Auto"));
            Assert.AreEqual(new ArrayLinear().GetWordList("Auto"), new CollectionBinary().GetWordList("Auto"));

            Assert.AreEqual(new ArrayBinary().GetWordList("Auto"), new CollectionBinary().GetWordList("Auto"));

            Assert.AreEqual(new CollectionLinear().GetWordList("Auto"), new ArrayBinary().GetWordList("Auto"));
            Assert.AreEqual(new CollectionLinear().GetWordList("Auto"), new CollectionBinary().GetWordList("Auto"));
        }
    }
}