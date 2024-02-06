/* Your code here! */
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <string>
#include "maze.h"
#include "cs225/PNG.h"
#include "dsets.h"
#include <queue>
#include <stack>
#include <utility>

SquareMaze::SquareMaze() {
    
    maze1 = new vector<Node>;
    disjointSets1 = new DisjointSets();
    width = 0;
    height = 0; 
    
}

SquareMaze::~SquareMaze() {
    
    delete maze1;
    maze1 = NULL;
    delete disjointSets1;
    disjointSets1 = NULL;
    
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    return true;
}

PNG * SquareMaze::drawMaze() const {
    return NULL;
}

PNG * SquareMaze::drawMazeWithSolution () {
    return NULL;
}

void SquareMaze::makeMaze(int width, int height) {

}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {

}

vector<int> SquareMaze::solveMaze() {
    vector<int> pee;
    return pee;
}