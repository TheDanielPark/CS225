/* Your code here! */
#include <stdlib.h>
#include <sys/stat.h>
#include <iostream>
#include <sstream>
#include <string>
#include "dsets.h"
#include "cs225/PNG.h"

using namespace std;

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        nodes.push_back(-1);
    }
}

int DisjointSets::find(int elem) {
    if (nodes[elem] < 0) {
        return elem;
    } else {
        int temp = find(nodes[elem]);
        nodes[elem] = temp;
        return temp;
    }
}

void DisjointSets::setunion(int a, int b) {
    a = find(a);
    b = find(b);

    int totalSize = nodes[a] + nodes[b];

    if (nodes[a] <= nodes[b]) {
        nodes[b] = a;
        nodes[a] = totalSize;
    } else {
        nodes[a] = b;
        nodes[b] = totalSize;
    }
}

int DisjointSets::size(int elem) {
    return -1 * nodes[find(elem)];
}