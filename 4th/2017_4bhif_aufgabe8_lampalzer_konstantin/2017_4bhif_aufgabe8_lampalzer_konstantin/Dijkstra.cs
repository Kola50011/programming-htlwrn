using System.Collections.Generic;
using System.Linq;

namespace _2017_4bhif_aufgabe8_lampalzer_konstantin
{
    public class Dijkstra
    {
        private readonly List<Node> _nodes;

        public Dijkstra(List<Node> nodes)
        {
            _nodes = nodes;
        }

        public double GetShortestPath(string startName, string endName)
        {
            Node start = _nodes.First(n => n.Name == startName);
            Node end = _nodes.First(n => n.Name == endName);
            List<Node> visited = new List<Node>();
            Dictionary<Node, double> distances = new Dictionary<Node, double>();
            List<Node> previous = new List<Node>();

            // Init distances with maxInt32
            foreach (Node node in _nodes) distances[node] = int.MaxValue;


            Node current = start;
            distances[current] = 0;

            while (!visited.Contains(end))
            {
                visited.Add(current);
                // Calculate all distances from current to unvisited neighbours
                foreach (Node neighbour in current.Neighbours.Keys.Except(visited))
                {
                    double newDistance = distances[current] + current.Neighbours[neighbour];
                    if (newDistance < distances[neighbour]) distances[neighbour] = newDistance;
                }

                // Get smallest unvisited
                current = distances.Where(n => !visited.Contains(n.Key)).Aggregate((l, r) => l.Value < r.Value ? l : r)
                    .Key;
            }

            return distances[end];
        }
    }
}