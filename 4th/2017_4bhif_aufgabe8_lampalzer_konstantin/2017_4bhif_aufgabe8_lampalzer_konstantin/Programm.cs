using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace _2017_4bhif_aufgabe8_lampalzer_konstantin
{
    public class Programm
    {
        public static void Main(string[] args)
        {
            Dictionary<string, Node> nodes = new Dictionary<string, Node>();
            string[] lines = File.ReadAllLines(
                @"C:\Users\Koka\Google Drive\Schule Koka\4. Klasse\POS\2017_4bhif_aufgabe8_lampalzer_konstantin\orte.csv");

            RouteManager routeManager = new RouteManager(lines);
            Console.WriteLine(routeManager);
            Console.ReadLine();

            foreach (string line in lines)
            {
                string[] columns = line.Split(';');
                if (!nodes.ContainsKey(columns[0]))
                {
                    nodes[columns[0]] = new Node();
                    nodes[columns[0]].Name = columns[0];
                }

                if (!nodes.ContainsKey(columns[1]))
                {
                    nodes[columns[1]] = new Node();
                    nodes[columns[1]].Name = columns[1];
                }

                nodes[columns[0]].Neighbours[nodes[columns[1]]] = double.Parse(columns[2]);
                nodes[columns[1]].Neighbours[nodes[columns[0]]] = double.Parse(columns[2]);
            }

            Dijkstra dijkstra = new Dijkstra(nodes.Values.ToList());
            Console.WriteLine(dijkstra.GetShortestPath("W", "I"));
            Console.ReadLine();
        }
    }
}