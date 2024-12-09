#include <iostream>
#include "Arrow.cpp"
#include <regex>
#include "LoopBack.cpp"
#include "keyValues.h"
#include "Block.cpp"
#include "VArrow.cpp"

void renderGrid(char grid[][GRID_X]) {
    for(int j = GRID_Y-1; j >= 0; j--) {
        for(int i = 0; i < GRID_X; i++) {
            std::cout << grid[j][i];
        }
        std::cout << std::endl;
    }
}

void parseInput(char grid[][GRID_X], std::string input) {
    int start = 0;
    int gridPos = 0;
    int loopBacks = 0;
    int sums[50]; // Max 50 sums because I'm lazy. TODO: figure out how dynamic memory allocation works without vectors.
    int nSums = 0;
    while(start < input.length()-1) {
        int end = input.find_first_of(' ', start+1);
        std::string substr = input.substr(start, end-start);
        if(substr.front() == '(') {
            Block block = Block(gridPos,GRID_Y/2-1,substr);
            block.draw(grid);
            gridPos += 4 + substr.length();
        } else if(substr.back() == '>') {
            Arrow arrow = Arrow(gridPos, GRID_Y/2, gridPos+7, GRID_Y/2);
            arrow.draw(grid);
            gridPos += 8;
        } else if(substr.front() == '<') {
            Arrow arrow = Arrow(gridPos+7, GRID_Y/2, gridPos, GRID_Y/2);
            arrow.draw(grid);
            gridPos += 8;
        } else if(substr.back() == ']') {
            int loopTo = std::stoi(substr.substr(5, substr.length()-6));
            LoopBack loopBack = LoopBack(gridPos, GRID_Y/2,  loopBacks*1+3, sums[loopTo-1]);
            loopBack.draw(grid);
            gridPos += 8;
            loopBacks++;
        } else if(substr.back() == '+') {
            grid[GRID_Y/2][gridPos] = '(';
            grid[GRID_Y/2][gridPos+1] = '+';
            grid[GRID_Y/2][gridPos+2] = ')';
            sums[nSums] = gridPos+1;
            nSums++;
            gridPos += 3;
        } else if(substr.back() == '}') {
            for(int i = 1; i < substr.length()-1; i++) {
                grid[GRID_Y/2][gridPos] = substr.at(i);
                gridPos++;
            }
        } else if(substr.front() == 'D') {
            Block disturbance = Block(gridPos+4, GRID_Y/2 + 3, substr.substr(1, substr.length()-1));
            disturbance.draw(grid);
            VArrow arrow = VArrow(gridPos+3, GRID_Y/2+4, gridPos-2, GRID_Y/2+1);
            arrow.draw(grid);
        }
        start = end+1;
    }


}

int main(int argc, char* argv[])  {

    char grid[GRID_Y][GRID_X] = {' '};
    for(int i = 0; i < GRID_X; i++) {
        for(int j = 0; j < GRID_Y; j++) {
            grid[j][i] = ' ';
        }
    }
    std::string command = argv[1]; //"{SP} -> + -> (K/3s+1) -> (1/s+1) [loop1] -> {TS} ";
    parseInput(grid, command);
    renderGrid(grid);
}



