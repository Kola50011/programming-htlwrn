using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace RomanTest
{
    [TestClass]
    public class RomanTest
    {
        [TestMethod]
        public void TestRomanToInt()
        {
            Assert.AreEqual(Roman.Roman.RomanToInt("M"), 1000);
            Assert.AreEqual(Roman.Roman.RomanToInt("XXVI"), 26);
            Assert.AreEqual(Roman.Roman.RomanToInt("IV"), 4);
        }

        [TestMethod]
        public void TestIntToRoman()
        {
            Assert.AreEqual(Roman.Roman.IntToRoman(1000), "M");
            Assert.AreEqual(Roman.Roman.IntToRoman(26), "XXVI");
            Assert.AreEqual(Roman.Roman.IntToRoman(4), "IV");
        }
    }
}