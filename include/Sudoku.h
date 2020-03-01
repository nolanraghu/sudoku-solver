/*
Name: Nolan Raghu
VUnetID: raghun
Email: nolan.raghu@vanderbilt.edu
Class: CS 3270 - Vanderbilt University
Date: 2/17/2020
Honor statement: I pledge on my honor that I have neither given nor received unauthorized aid on
this examination.”


 */
#ifndef SUDOKU_H
#define SUDOKU_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Sudoku {
private:
    /**
     * 9X9 int array that holds the digits of the puzzle. Stores 0 if the space is empty
     */
    int puzzleGrid[9][9];

    /**
     * Helper method for validSquare
     * Checks if num is in the 3x3 sudoku nonant that contains of coordinate (x,y)
     * @param x: x-coordinate being checked
     * @param y: y-coordinate being checked
     * @param num: number being checked
     * @return true if num is not in the nonant
     */
    bool quadCheck(int x, int y, int num);

    /**
     * Helper function of writeNumber
     * Checks if num a valid choice in position (x,y)
     * @param x: x-coordinate
     * @param y: y-coordinate
     * @param num: number being checked
     * @return true if num is a valid choice
     */
    bool validSquare(int x, int y, int num);

    /**
     * Helper function of writeNumber
     * Calls writeNumber on the next unchecked position in the puzzle
     * @param x: x-coordinate
     * @param y: y-coordinate
     * @return true if a valid number can be found at (x,y) and all yet unchecked position on the
     * board
     */
    bool recurser(int x, int y);

    /**
     * Recursive function that fills the open slots of the puzzle with valid numbers by calling
     * recurser
     * @param x: x-coordinate
     * @param y: y-coordinate
     * @return true if a valid number can be found at (x,y) and all yet unchecked position on the
     * board
     */
    bool writeNumber(int x, int y);

public:
    /**
     * Default constructor of the Sudoku class that initializes the puzzleGrid to an array of 0s.
     */
    Sudoku();

    /**
     * loads a sudoku puzzle into puzzleGrid from a .txt file
     */
    void loadFromFile(const std::string& filename);

    /**
     * Tests for equality between two puzzles
     * @param other: the puzzle being compares to *this
     * @return true if they're the same, false otherwise
     */
    bool equals(const Sudoku& other);

    /**
     * Overloaded << operator for the Sudoku class.
     * @param out: ostream that sudoku is being inserted into
     * @param sudoku: sudoku object being extracted
     * @return out w/sudoku inserted
     */
    friend std::ostream& operator<<(std::ostream& out, const Sudoku& sudoku);

    /**
     * Solves the puzzle in puzzleGrid. Leaves puzzleGrid in a 'solved' state
     * @return true if the puzzle can be solved
     */
    bool solve();
};

#endif