/* Your code here! */
/* Your code here! */
#pragma once

#include <string>
#include <vector>
#include "cs225/PNG.h"

using namespace std;


class DisjointSets {
    public : 
    void addelements(int num);
    int find(int elem);
    void setunion(int a, int b);
    int size(int elem);

    private:
        vector<int> nodes;
};

