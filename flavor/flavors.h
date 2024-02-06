

#pragma once

#include <vector>
#include <algorithm>
#include <tuple>
#include <map>
#include <utility>
#include "graph.h"
#include "edge.h"

using namespace std;
/**
 * Represents a algorithm to learn the game of Nim.
 */
class Flavors {
public:
  /**
   * Constructor to create a graph of flavors from dataset
   */
  Flavors(string filename);
  //constructor to build flavors graph based on region?
  //Flavors(unsigned startingTokens);

  /**
  * Reads the dataset of food connections with weighted edges based on shared
  * chemical compounds
  */
  vector<tuple<string, string, int>> _flavorFileParser(string filename);

  /**
  * Reads the dataset of food and which category they are in, returns a map with 
  * food as key and category as value
  */
  map<string, string> _categoryFileParser();

  /**
  * Returns upper and lower bound edge weights for graph traversal
  */
  pair<int, int> getBounds(string inputFood);

  /**
   * Returns a constant reference to the state space graph.
   *
   * @returns A constant reference to the state space graph.
   */
  const Graph & getGraph() const;


  /**
   * Returns the list of complementary foods
   */
  void combinations(Vertex food);

  /**
   * Returns output
   */
  vector<Vertex> outputFood();

  void shortestPath(Vertex start, Vertex end);

  int minDistance(int dist[], bool spltSet[]);
  

  void BFS(Vertex filler);

private:
  Graph g_;
  Vertex startingVertex_;
  vector<tuple<string, string, int>> flavorEdges;
  map<string, string> categories;
  vector<Vertex> output;
  map<Vertex, bool> visited; 
  Graph combos;
  std::priority_queue<Vertex, vector<Vertex>, std::greater<Vertex>> minHeap;
  
};
