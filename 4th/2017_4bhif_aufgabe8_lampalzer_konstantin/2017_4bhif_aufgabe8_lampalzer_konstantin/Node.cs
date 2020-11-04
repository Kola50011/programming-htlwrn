using System.Collections.Generic;

namespace _2017_4bhif_aufgabe8_lampalzer_konstantin
{
    public class Node
    {
        public string Name { get; set; }
        public Dictionary<Node, double> Neighbours { get; set; } = new Dictionary<Node, double>();
    }
}