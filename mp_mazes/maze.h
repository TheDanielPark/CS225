/* Your code here! */
#pragma once

#include <string>
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
#include <utility>
#include "cs225/HSLAPixel.h"

using namespace std;
using namespace cs225;

class SquareMaze {
    public : 
    SquareMaze();
    bool canTravel(int x, int y, int dir) const;
    PNG * drawMaze() const;
    PNG * drawMazeWithSolution();
    void makeMaze(int width, int height);
    void setWall(int x, int y, int dir, bool exists);
    vector<int> solveMaze();
    ~SquareMaze();

    private:
    
        struct Node {
            bool right = true;
            bool down = true;
            int x;
            int y;
        };
    int width;
    int height;
    vector<Node> * maze1;
    DisjointSets * disjointSets1;
    

};