//
// Created by Dylan Beaumont on 8/9/2024.
//

#include <string>
#include "keyValues.h"

class LoopBack {
public:
    int fromX, fromY, dropDepth, toX;

    LoopBack(int inputFromX, int inputFromY, int inputDropDepth, int inputToX) {
        fromX = inputFromX;
        fromY = inputFromY;
        dropDepth = inputDropDepth;
        toX = inputToX;
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

    void draw(char grid[][GRID_X]) {
        drawSegment(grid, fromX, fromY, fromX+7, fromY, false);
        drawSegment(grid, fromX+7, fromY, fromX+7, fromY-dropDepth, true);
        drawSegment(grid, fromX+7, fromY-dropDepth, toX, fromY-dropDepth, true);
        drawSegment(grid, toX, fromY-dropDepth, toX, fromY-1, true);
    }

};
