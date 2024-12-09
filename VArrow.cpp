//
// Created by Dylan Beaumont on 8/9/2024.
//

#include <string>
#include "keyValues.h"

class VArrow {
public:
  int fromX, fromY, toX, toY;

  VArrow(int inputFromX, int inputFromY, int inputToX, int inputToY) {
    fromX = inputFromX;
    fromY = inputFromY;
    toX = inputToX;
    toY = inputToY;
  }

  void draw(char grid[][GRID_X]) const {
    // generate the coordinates of segements.
    if( fromX == toX or fromY == toY ) {
      drawSegment(grid, fromX, fromY, toX, toY, false);
    } else {
      // always leave horizontally and connect vertically
      drawSegment(grid, fromX, fromY, toX, fromY, false);
      drawSegment(grid, toX, fromY, toX, toY, true);
    }
  }

  static void drawSegment(char grid[][GRID_X], const int fromX, const int fromY, const int toX, const int toY, const bool joint) {
    if(fromY == toY) { // horizontal step
      int steps = std::abs(toX-fromX);
      const int step = (toX-fromX)/steps;
      int x = fromX;
      if(joint) {
        grid[toY][x] = '*';
        x += step;
        steps--;
      }
      while(steps > 0) {
        grid[toY][x] = '-';
        x += step;
        steps--;
      }
      step > 0 ? grid[toY][toX] = '>': grid[toY][toX] = '<';

    } else if(fromX == toX) { // vertical step
      int steps = std::abs(toY-fromY);
      const int step = (toY-fromY)/steps;
      int y = fromY;
      if(joint) {
        grid[y][toX] = '*';
        y += step;
        steps--;
      }
      while(steps > 0) {
        grid[y][toX] = '|';
        y += step;
        steps--;
      }
      step > 0 ? grid[toY][toX] = '^': grid[toY][toX] = 'v';
    }
  }

};

