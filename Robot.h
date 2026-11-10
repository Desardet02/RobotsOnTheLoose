//
// Created by William Wright on 11/5/26.
//

#ifndef CSCI1300_CS1_ROBOT_H
#define CSCI1300_CS1_ROBOT_H

#include <string>

using namespace std;

class Robot {
    static const int MAX_MOVE_SIZE = 3;

    string name;
    int x;
    int y;
    int gridSize;

    int randomInt();
public:
    Robot(string name, int x, int y, int gridSize);

    string getName();

    void move(int dx, int dy);
    void printStatus();

    bool atPosition(int posX, int posY);

    void makeRandomMove();

    int getX();
    int getY();
};


#endif //CSCI1300_CS1_ROBOT_H
