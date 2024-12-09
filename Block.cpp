//
// Created by Dylan Beaumont on 8/9/2024.
//

#include <string>
#include "keyValues.h"

class Block {
public:
    int x;
    int y;
    std::string g;
    Block* connectsTo[];
    Block(int inputX, int inputY, std::string inputG) {
        x = inputX;
        y = inputY;
        g = std::move(inputG);
    }
    void draw(char grid[][GRID_X]) {
        int width = g.length() + 4;
        int height = 3;
        if(x+width > GRID_X) width = GRID_X-x;
        for(int i=x; i<x+width; i++) {
            grid[y][i] = '-';
            grid[y+height-1][i] = '-';
        }
        for(int i = 0; i < g.length(); i++) {
            grid[y+1][x+2+i] = g.at(i);
        }
        for(int j = y+1; j<y+height-1; j++) {
            grid[j][x] = '|';
            grid[j][x+width-1] = '|';
        }
    }
};
