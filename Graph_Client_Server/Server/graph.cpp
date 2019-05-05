#include "graph.h"

Graph::Graph() {
    Node *eisenstadt = new Node("Eisenstadt", 10);
    Node *klagenfurt = new Node("Klagenfurt", 11);
    Node *sankt = new Node("Sankt Pölten", 5);
    Node *linz = new Node("Linz", 5);
    Node *salzburg = new Node("Salzburg", 4);
    Node *graz = new Node("Graz", 3);
    Node *innsbruck = new Node("Innsbruck", 3);
    Node *bregenz = new Node("Bregenz", 8);
    Node *wien = new Node("Wien", 1);

    nodes.push_back(eisenstadt);
    nodes.push_back(klagenfurt);
    nodes.push_back(sankt);
    nodes.push_back(linz);
    nodes.push_back(salzburg);
    nodes.push_back(graz);
    nodes.push_back(innsbruck);
    nodes.push_back(bregenz);
    nodes.push_back(wien);

    eisenstadt->add_neighbour(sankt, 67);
    eisenstadt->add_neighbour(graz, 106);
    eisenstadt->add_neighbour(wien, 47);

    klagenfurt->add_neighbour(graz, 144);
    klagenfurt->add_neighbour(innsbruck, 240);
    klagenfurt->add_neighbour(salzburg, 144);

    sankt->add_neighbour(wien, 61);
    sankt->add_neighbour(linz, 74);
    sankt->add_neighbour(graz, 161);
    sankt->add_neighbour(eisenstadt, 67);

    linz->add_neighbour(sankt, 74);
    linz->add_neighbour(graz, 147);
    linz->add_neighbour(salzburg, 77);

    salzburg->add_neighbour(linz, 77);
    salzburg->add_neighbour(graz, 180);
    salzburg->add_neighbour(klagenfurt, 144);
    salzburg->add_neighbour(innsbruck, 132);

    graz->add_neighbour(eisenstadt, 106);
    graz->add_neighbour(sankt, 161);
    graz->add_neighbour(linz, 147);
    graz->add_neighbour(salzburg, 180);
    graz->add_neighbour(klagenfurt, 144);

    innsbruck->add_neighbour(salzburg, 132);
    innsbruck->add_neighbour(bregenz, 130);

    bregenz->add_neighbour(innsbruck, 130);

    wien->add_neighbour(eisenstadt, 47);
    wien->add_neighbour(sankt, 61);
}

std::vector<Node*> Graph::get_route(std::string from, std::string to)
{
    std::vector<Node*> route;
    std::unordered_map<Node*, int> cost_to_node;
    std::unordered_map<Node*, Node*> path_to_node;

    std::priority_queue<std::pair<int, Node*>,
            std::vector<std::pair<int, Node*>>,
            std::greater<std::pair<int, Node*>>> prio_queue;

    Node* start = get_node_from_name(from);
    Node* destination = get_node_from_name(to);

    prio_queue.push(std::make_pair(start->value, start));

    bool done = false;
    while (prio_queue.size() != 0 && !done) {
        Node* current = prio_queue.top().second;
        prio_queue.pop();

        Node* neighbour_node;
        int conn_cost;

        for (auto neighbour : current->connected) {
            std::tie(neighbour_node, conn_cost) = neighbour;

            int new_cost = cost_to_node[current] + conn_cost + neighbour_node->value;
            if (neighbour_node->name == destination->name) {
                path_to_node[neighbour_node] = current;
                std::cout << "Found end with " + std::to_string(new_cost) + " from " + current->name << std::endl;
                done = true;
            } else if (cost_to_node.find(neighbour_node) == cost_to_node.end() || cost_to_node[neighbour_node] > new_cost) {
                std::cout << "Adding " + neighbour_node->name << std::endl;
                path_to_node[neighbour_node] = current;
                cost_to_node[neighbour_node] = new_cost;
                prio_queue.push(std::make_pair(new_cost, neighbour_node));
            }
        }

    }

    if (done) {

        Node* n = destination;
        while (n->name != start->name) {
            route.push_back(n);
            n = path_to_node[n];
        }
        route.push_back(n);

    }

    std::reverse(route.begin(), route.end());

    return route;
}

std::vector<std::vector<Node *> > Graph::get_route_breadth_first_search(std::string from, std::string end)
{
    std::vector<std::vector<Node*>> routes;

    Node* start = get_node_from_name(from);
    Node* destination = get_node_from_name(end);

    std::unordered_map<Node*, std::vector<Node*>> predecessors;
    std::deque<Node*> to_visit;

    to_visit.push_front(start);

    while (to_visit.size() != 0) {
        auto* current = to_visit.back();
        to_visit.pop_back();

        for (auto& pair : current->connected) {
            if (std::find(predecessors[pair.first].begin(), predecessors[pair.first].end(), current) == predecessors[pair.first].end()) {
                predecessors[pair.first].push_back(current);
                to_visit.push_front(pair.first);
            }
        }

        if (current == destination) {
            break;
        }
    }


    auto& tmp = backtracking(predecessors, start, destination);
//    for (auto& route : tmp) {
//        for (auto* node : route) {
//            std::cout << node->name << " ";
//        }
//        std::cout << std::endl;
//    }

    return routes;

}

std::vector<std::vector<Node *>>& Graph::backtracking(std::unordered_map<Node *, std::vector<Node *> >& predecessors, Node *start_node, Node *destination)
{
    std::vector<std::vector<Node*>> route;
    if (start_node != destination) {
        for (auto& node : predecessors[start_node]) {
            auto _route = backtracking(predecessors, node, destination);
            for (auto& r : _route) {
                r.push_back(start_node);
                route.push_back(r);
            }
        }
    } else {
        std::vector<std::vector<Node *> > tmp{{start_node}};
        return tmp;
    }
    return route;
}



Node *Graph::get_node_from_name(std::string name)
{
    for (auto* n : nodes) {
        if (n->name == name) {
            return n;
        }
    }
    throw std::logic_error{"Name " + name + " not found in Graph!"};
}
