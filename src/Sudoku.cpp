/*
Name: Nolan Raghu
VUnetID: raghun
Email: nolan.raghu@vanderbilt.edu
Class: CS 3270 - Vanderbilt University
Date: 2/17/2020
Honor statement: I pledge on my honor that I have neither given nor received unauthorized aid on
this examination.”


 */
#ifndef SUDOKU_CPP
#define SUDOKU_CPP

#include "Sudoku.h"
#include <fstream>
#include <iostream>

Sudoku::Sudoku()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            puzzleGrid[i][j] = 0;
        }
    }
}

void Sudoku::loadFromFile(const std::string& filename)
{
    int inDigit, row = 0, col = 0;
    std::ifstream file(filename);
    while (file >> inDigit) {
        if (row == 9) {
            ++col;
            row = 0;
        }
        puzzleGrid[col][row] = inDigit;
        row++;
    }
}

bool Sudoku::equals(const Sudoku& other)
{
    bool target = true;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (puzzleGrid[i][j] != other.puzzleGrid[i][j]) {
                target = false;
            }
        }
    }
    return target;
}

std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku)
{
    std::string product;
    for (int j = 0; j < 9; j++) {
        if (j == 3 || j == 6) {
            product.append("------+-------+------");
            product += "\n";
        }
        for (int i = 0; i < 9; i++) {
            if (sudoku.puzzleGrid[j][i] != 0) {
                product += std::to_string(sudoku.puzzleGrid[j][i]);
            } else {
                product += " ";
            }
            product += " ";
            if (i == 2 || i == 5) {
                product += "|";
                product += " ";
            }
        }
        product += "\n";
    }
    out << product;
    return out;
}

bool Sudoku::quadCheck(int x, int y, int num)
{
    int xOffset, yOffset;
    bool target = true;
    if (x > 5) {
        xOffset = 6;
    } else {
        xOffset = (x > 2) ? 3 : 0;
    }
    if (y > 5) {
        yOffset = 6;
    } else {
        yOffset = (y > 2) ? 3 : 0;
    }

    // checks the 3x3 for num
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (puzzleGrid[i + xOffset][j + yOffset] == num) {
                target = false;
            }
        }
    }
    return target;
}

bool Sudoku::validSquare(int x, int y, int num)
{

    bool target = true;

    // checks the column for num
    for (int i = 0; i < 9; ++i) {
        if (puzzleGrid[x][i] == num) {
            target = false;
        }
    }

    // checks the row for num
    for (int i = 0; i < 9; ++i) {
        if (puzzleGrid[i][y] == num) {
            target = false;
        }
    }
    return (target && quadCheck(x, y, num));
}

bool Sudoku::recurser(int x, int y)
{
    if (y == 9) {
        return writeNumber(x + 1, 0);
    } else {
        return writeNumber(x, y);
    }
}

bool Sudoku::writeNumber(int x, int y)
{
    // Occurs if the whole board has been checked
    if (x > 8) {
        return true;
    }

    // checks if (x,y) is a preset number
    if (puzzleGrid[x][y] != 0) {
        return recurser(x, y + 1);
    }

    for (int num = 1; num < 10; ++num) {
        if (validSquare(x, y, num)) {
            puzzleGrid[x][y] = num;
            if (recurser(x, y + 1)) { // checks if next square is valid;
                return true;
            }
            puzzleGrid[x][y] = 0;
        }
    }
    return false;
}

bool Sudoku::solve()
{
    return writeNumber(0, 0);
}

#endif