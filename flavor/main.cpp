#include "flavors.h"
#include <vector>
#include "edge.h"

int main() {
  
  //Construct initial flavor graph
  
  //User input
  string inputFood, inputFile;

  //Take in input ingredient 
  cout << "Welcome to Flavortown! Tell us the input filename." << endl;
  cin >> inputFile;
  Flavors flavor(inputFile);
  cout << "Welcome to Flavortown! Which ingredient would you like to use?" << endl;
  cin >> inputFood; 

  ofstream myfile;
  myfile.open ("combos.txt");
  flavor.combinations(inputFood);

  vector<Vertex> output = flavor.outputFood();
  for(unsigned i = 0; i < output.size(); i++) {
    myfile << output[i] << std::endl;
  }

  //cout << "Welcome to Flavortown! Which ingredient would you like to use?" << endl;
  //cin >> inputFood;
  //BFS("bacon");
  return 0;
}