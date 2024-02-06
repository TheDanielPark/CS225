#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  trav_ = NULL;
  curr = Point();

}
//Added a constructor for begin
ImageTraversal::Iterator::Iterator(PNG & png, Point & start, double tolerance, ImageTraversal * trav) {
  start_ = start;
  tolerance_ = tolerance;
  png_ = png;
  trav_ = trav;
  curr = trav_->peek();
  beenVisited.resize(png_.height() * png_.width(), false);
}
//Returns true if it is in bounds of the image & tolerance, false if it is not
bool ImageTraversal::Iterator::inBounds(const Point & direction) const {
  if (direction.x < png_.width() && direction.y < png_.height() && 
      calculateDelta(png_.getPixel(direction.x, direction.y), png_.getPixel(start_.x, start_.y)) <= tolerance_) {
      return true;
  }
  return false;
}


/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  unsigned int bound = png_.width() * png_.height();
  /* for (unsigned int i = 0; i < bound; i++) {
    beenVisited[i] = false;
  } */
  if (trav_->empty() == false) {
    unsigned location = (curr.y * png_.width()) + curr.x;
    beenVisited[location] = true;
    trav_->pop();

    Point right = Point(curr.x + 1, curr.y);
    Point below = Point(curr.x, curr.y + 1);
    Point left  = Point(curr.x - 1, curr.y);
    Point above = Point(curr.x, curr.y - 1);

    while (trav_->empty() == false && beenVisited[(trav_->peek().y * png_.width()) + trav_->peek().x] == true) {
      trav_->pop();
    } 

    if (inBounds(right) == true && beenVisited[(right.y * png_.width()) + right.x] == false) {
      trav_->add(right);
    }
    if (inBounds(below) == true && beenVisited[(below.y * png_.width()) + below.x] == false) {
      trav_->add(below);
    }
    if (inBounds(left) == true && beenVisited[(left.y * png_.width()) + left.x] == false) {
      trav_->add(left);
    }
    if (inBounds(above) == true && beenVisited[(above.y * png_.width()) + above.x] == false) {
      trav_->add(above);
    }
    if (trav_->empty() == false) {
      curr = trav_->peek();
    }


  }
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //taken from lab trees
  bool thisEmpty = false; 
  bool otherEmpty = false;

  if (trav_ == NULL) { thisEmpty = true; }
  if (other.trav_ == NULL) { otherEmpty = true; }

  if (!thisEmpty)  { thisEmpty = trav_->empty(); }
  if (!otherEmpty) { otherEmpty = other.trav_->empty(); }

  if (thisEmpty && otherEmpty) return false; // both empty then the traversals are equal, return true
  else if ((!thisEmpty)&&(!otherEmpty)) return (trav_ != other.trav_); //both not empty then compare the traversals
  else return true; // one is empty while the other is not, return true
  
}

