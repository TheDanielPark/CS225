/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <vector>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    if (first[curDim] < second[curDim]) {
      return true;
    } else if (first[curDim] == second[curDim]) {
      return first < second;
    } else {
      return false;
    }


}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
    int cDist = 0;
    int pDist = 0;
    for (unsigned i = 0; i < Dim; i++) {
      cDist += (target[i] - currentBest[i]) * (target[i] - currentBest[i]);
      pDist += (target[i] - potential[i]) * (target[i] - potential[i]);
    }
    if (pDist < cDist) {
      return true;
    } else if (pDist == cDist) {
      return potential < currentBest;
    } else {
      return false;
    }
  
}

template <int Dim>
unsigned KDTree<Dim>::partition(vector<Point<Dim>> & list, unsigned left, unsigned right, unsigned pivotIndex, unsigned dim) {
  Point<Dim> pivotValue = list[pivotIndex];
  Point<Dim> temp = list[pivotIndex];
  list[pivotIndex] = list[right];
  list[right] = temp;
  unsigned storeIndex = left;
  for (unsigned i = left; i < right; i++) {
    if (smallerDimVal(list[i], pivotValue, dim)) {
      temp = list[storeIndex];
      list[storeIndex] = list[i];
      list[i] = temp;
      storeIndex++;
    }
  }
  temp = list[storeIndex];
  list[storeIndex] = list[right];
  list[right] = temp;
  return storeIndex;
}

template <int Dim>
Point<Dim> & KDTree<Dim>::quickSelect(vector<Point<Dim>> & list, unsigned left, unsigned right, unsigned k, unsigned dim) {
  if (left == right) {
    return list[left];
  }
  unsigned pivotIndex = k;
  pivotIndex = partition(list, left, right, pivotIndex, dim);
  if (k == pivotIndex) {
    return list[k];
  } else if (k < pivotIndex) {
    return quickSelect(list, left, pivotIndex - 1, k, dim);
  } else {
    return quickSelect(list, pivotIndex + 1, right, k, dim);
  }
  
}

template <int Dim>
typename KDTree<Dim>::KDTreeNode* KDTree<Dim>::buildTree(vector<Point<Dim>> & points, unsigned dim, unsigned left, unsigned right) {
  if (left > right) {
    return NULL;
  }
  if (left < 0 || right < 0 || left >= points.size() || right >= points.size() || points.empty()) {
    return NULL;
  }
  unsigned middle = (left + right) / 2;
  KDTreeNode * currRoot = new KDTreeNode(quickSelect(points, left, right, middle, dim));
  //size++;
  
  currRoot->left = buildTree(points, (dim + 1) % Dim, left, middle - 1);
  currRoot->right = buildTree(points, (dim + 1) % Dim, middle + 1, right);
  return currRoot;
}



template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    size = newPoints.size();
    vector<Point<Dim>> points(newPoints);
    //points.assign(newPoints.begin(), newPoints.end());
    root = buildTree(points, 0, 0, points.size() - 1);
}

template <int Dim>
void KDTree<Dim>::copy(KDTreeNode *& subroot, KDTreeNode * node) {
  if (node == NULL) {
    return;
  }
  //size++;
  subroot = new KDTreeNode(*node);
  copy(subroot->left, node->left);
  copy(subroot->right, node->right);

}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  copy(root, other.root);
  size = other.size;
  
}

template <int Dim>
void KDTree<Dim>::deleteHelper(KDTreeNode * node) {
  if (node == NULL) {
    return;
  }
  deleteHelper(node->left);
  deleteHelper(node->right);
  delete node;
  node = NULL;
  //size--;
}
template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  deleteHelper(root);
  root = NULL;
  copy(root, rhs.root);
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
  deleteHelper(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    Point<Dim> near;
    double distance = -1;
    findNearestNeighbor(root, query, near, distance, 0);

    return near;
}

template <int Dim>
void KDTree<Dim>::findNearestNeighbor(KDTreeNode * node, const Point<Dim> & query, Point<Dim> & near, double & distance, int dim) const {
  if (node == NULL) {
    return;
  }
  KDTreeNode * close;
  KDTreeNode * far;

  if (smallerDimVal(query, node->point, dim)) {
    close = node->left;
    far = node->right;
  } else {
    close = node->right;
    far = node->left;
  }
  if (close && (distance < 0 || (distance+query[dim] >= node->point[dim] || query[dim] - distance <= node->point[dim]))) {
    findNearestNeighbor(close, query, near, distance, (dim + 1) % Dim);
  }
  if (distance < 0 || shouldReplace(query, near, node->point)) {
    near = node->point;
    distance = 0;
    for (int i = 0; i < Dim; i++) {
      distance += (query[i] - near[i]) * (query[i] - near[i]);
    }
    distance = sqrt(distance);
  }
  if (far && (distance + query[dim] >= node->point[dim] && query[dim] - distance <= node->point[dim])) {
    findNearestNeighbor(far, query, near, distance, (dim+1) % Dim);
  }
}

