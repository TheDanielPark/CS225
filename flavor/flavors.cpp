//
//class
//public: constructor, readFile, traversal, display, 
//private: graph
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <iostream>
#include "flavors.h"
#include "graph.h"
#include <boost/algorithm/string.hpp>
using namespace std;


Flavors::Flavors(string filename) : g_(true, false), combos(true, false) {
    flavorEdges = _flavorFileParser(filename);
    categories = _categoryFileParser();
    
    for (unsigned i = 0; i < flavorEdges.size(); i++) {
        string food1 = get<0>(flavorEdges[i]);
        string food2 = get<1>(flavorEdges[i]);
        int weight = get<2>(flavorEdges[i]);

        if (!g_.vertexExists(food1)) {
            g_.insertVertex(food1);
            minHeap.push(food1);
        } 
        
        if (!g_.vertexExists(food2)) {
            g_.insertVertex(food2);
            minHeap.push(food2);
        }
        g_.insertEdge(food1, food2);
        g_.setEdgeWeight(food1, food2, weight);

    }
    //g_.print();
    // // g_.initSnapshot("graph");
    // // g_.snapshot();
    //g_.savePNG("grapher");
    if (filename == "flavors.csv") {
        BFS("bacon");
    } else {
        BFS(g_.getStartingVertex());
    }
    g_.print();
}


void Flavors::combinations(Vertex food) {
    
    vector<Vertex> adj = g_.getAdjacent(food);
    if(output.size() >= 8 || adj.size() == 0) {
        return;
    }
    pair<int, int> bounds = getBounds(food);
    for(unsigned i = 0; i < adj.size(); i++) {
        if(bounds.first < g_.getEdge(food, adj[i]).getWeight() && bounds.second > g_.getEdge(food, adj[i]).getWeight() &&
            categories[food] != categories[adj[i]]) {

            if(visited[adj[i]] == false) {
                if (!combos.vertexExists(food)) {
                    combos.insertVertex(food);
                } 
                if (!combos.vertexExists(adj[i])) {
                    combos.insertVertex(adj[i]);
                }
                combos.insertEdge(food, adj[i]);
                combos.setEdgeWeight(food, adj[i], g_.getEdgeWeight(food, adj[i]));
                output.push_back(adj[i]);
                visited[adj[i]] = true;
                combinations(adj[i]);
            }
        }
        if(output.size() >= 8) {
            break;
        }
    }
    
}



vector<Vertex> Flavors::outputFood() {
    combos.savePNG("combos");
    return output;
}

vector<tuple<string, string, int>> Flavors::_flavorFileParser(string filename) {
    //open file
    std::ifstream text(filename);
    //return vector with edges
    vector<tuple<string, string, int>> edges;
	if (text.is_open()) {
		std::istream_iterator<std::string> iter(text);
        //iterate through entire file;
		while (!text.eof()) {
            stringstream stream(*iter);
            //temp string 
            string elem;
            vector<string> row;
            
            //set elem by using ',' as delimiter
            while (getline(stream,elem,',')) {
                //insert elem into row vector
                row.push_back(elem);
              
            }

            tuple<string, string, int> flavorEdge = {row[0], row[1], stoi(row[2])};
            //insert tuple into return vector
            edges.push_back(flavorEdge);
            //std::cout << get<2>(flavorEdge) << std::endl;

            //next line
			++iter;
		}
	}
    return edges;
}

map<string, string> Flavors::_categoryFileParser() {
    
    map<string, string> category;
    //open the file
    ifstream fin("ingr_info.tsv");
    string line; 
        //loop through the file and set the values into the map
        while (getline(fin, line)) {
            vector<string> parts;
            split(parts, line, boost::is_any_of("\t"));
            category.insert(pair<string, string>(parts[1], parts[2]));
            /*for (auto& i : category) {
                cout << i.first << " " << i.second << endl;
            } */
           
        }
        fin.close();
        return category;
}

const Graph & Flavors::getGraph() const {
  return g_;
}


pair<int, int> Flavors::getBounds(string inputFood) {
    //Turn string into vertex?
    Vertex food = inputFood;
    //Vector of adjacent vertices
    vector<Vertex> startingAdjacent = g_.getAdjacent(food);
    //Mean and standard deviation
    int mean = 0;
    int sd = 5;

    //Get the sum of all weighted edges and find the mean
    for(unsigned i = 0; i < startingAdjacent.size(); i++) {
        mean += g_.getEdge(food, startingAdjacent[i]).getWeight();
    }
    mean = mean / startingAdjacent.size();

    //Return pair of lower and upper bound
    return pair<int, int>(mean - sd, mean + sd);
}

void Flavors::BFS(Vertex ingredient) {
    map<string, bool> visited;
    ofstream myfile;
    myfile.open ("BFS.txt");
    list<Vertex> queue;
    //have to get the id# of ingredient
    
    visited[ingredient] = true;
    queue.push_back(ingredient);

    //list<Vertex>::iterator it;
    Vertex tempPrint;
    while (!(queue.empty())) {
        ingredient = queue.front();
        myfile << ingredient << endl;
        //cout << ingredient << " ";
        queue.pop_front();
    
        vector<Vertex> temp = g_.getAdjacent(ingredient);
        //it = g_.getAdjacent(filler);
        for (auto j = temp.begin(); j != temp.end(); ++j) {
            if (visited[*j] == false) {
                visited[*j] = true;
                queue.push_back(*j);
                //tempPrint = queue.front();
                //cout << tempPrint << " ";
            }
        }
    }
    //cout << "\n";
    myfile.close();
}

void Flavors::shortestPath(Vertex start, Vertex end) {
    Vertex dist[1529];
    bool sptSet[1529];
    Graph min;

    for (int i = 0; i < 1529; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[0] = 0;
    
    for (int count = 0; count < 1529; count++) {
        Vertex m = minHeap.pop();
        // int u = minDistance(dist, sptSet);
        // sptSet[u] = true;
        T.add(m);
        std::vector<Vertex> verticies = g_.getVertices(m);

        for (unsigned i = 0; i < verticies.size(); i++) {
            if (dist[])
        }
        
    }
}

int Flavors::minDistance(int dist[], bool sptSet[]) 
{ 
    // Initialize min value 
    int min = INT_MAX, min_index; 
  
    for (int v = 0; v < 1529; v++) 
        if (sptSet[v] == false && dist[v] <= min) 
            min = dist[v], min_index = v; 
  
    return min_index; 
} 