//
// Created by William Wright on 11/5/26.
//

#include "Robot.h"
#include <iostream>
#include <random>

using namespace std;

int Robot::randomInt() {
    static random_device rd;
    static mt19937 generator(rd());

    // random values should be between -3 and +3
    uniform_int_distribution<int> distribution(-MAX_MOVE_SIZE, MAX_MOVE_SIZE);
    return distribution(generator);
}

Robot::Robot(string aName, int initX, int initY, int maxDimension) {
    name = aName;
    x = initX;
    y = initY;
    gridSize = maxDimension;
}

string Robot::getName() {
    return name;
}

bool Robot::atPosition(int posX, int posY) {
    return (x == posX) && (y == posY);
}

void Robot::printStatus() {
    cout << "Robot " << name << " is at position (" << x << ", " << y << ")" << endl;
}

void Robot::makeRandomMove() {
    ////////////////////////////////////////////////////////////
    // TODO (Question 4A):
    //  This function will move the robot to a new random position
    //  - The member function randomInt is already completed. 
    //      Use it to obtain random x and y distances to travel
    //  - Call the member function move (problem 4B) to move the robot in the random direction
    ////////////////////////////////////////////////////////////
    // YOUR CODE HERE:
    int dx = randomInt();
    int dy = randomInt();
    move(dx, dy);
}

void Robot::move(int dx, int dy) {
    ////////////////////////////////////////////////////////////
    // TODO (Question 4B):
    //  This function will move the robot
    //  - Move the robot by dx along the x axis, dy along the y axis
    //  - If the robot moves out of bounds, it should wrap around. Use mod for this (%)
    //  - Example: if x = gridSize-1 and dx is +1, we should move to x = 0
    ////////////////////////////////////////////////////////////
    // UPDATE THE TWO LINES BELOW:
    x = ((x + dx) % gridSize + gridSize) % gridSize;
    y = ((y + dy) % gridSize + gridSize) % gridSize;
}

int Robot::getX() {
    return x;
}

int Robot::getY() {
    return y;
}
