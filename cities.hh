/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>

#include <istream>
#include <ostream>
#include <iostream>

// Representation of an ordering of cities
class Cities {
 public:
  //ALIASES:
  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>;
  // An ordering of cities. Each value represents a unique index
  // into the current city ordering.
  using permutation_t = std::vector<unsigned int>;
  // The data type used to contain the cities in a Cities object.
  // Each coord_t entry in the vector represents a city.
  using cityCollection_t = std::vector<coord_t>;

  //METHODS:
  // Given a permutation, return a new Cities object where the order of the
  // cities reflects the original order of this class after reordering with
  // the given ordering. So for example, the ordering { 1, 0 } simply swaps
  // the first two elements (coordinates) in the new Cities object.
  Cities reorder(const permutation_t& ordering) const;

  // For a given permutation of the cities in this object,
  // compute how long (distance) it would take to traverse all the cities in the
  // order of the permutation, and then returning to the first city.
  // The distance between any two cities is computed as the Euclidean
  // distance on a plane between their coordinates.
  double total_path_distance(const permutation_t& ordering) const;

  //OPERATOR OVERLOADS:
  friend std::istream& operator>> (std::istream& iS, Cities& c);

  //DATA:
  // A vector containing the coord_t's of each city in the object.
  cityCollection_t my_Cities;

};
