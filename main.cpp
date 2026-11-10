#include <iostream>
#include <fstream>
#include <optional>
#include <random>
#include <vector>

#include "Robot.h"

using namespace std;

optional<Robot> createRobotFromStream(istream& robotStream, int maxDimension) {
    // Robot file looks like this:
    string name;
    int x, y;
    ////////////////////////////////////////////////////////////
    // TODO (Question 3):
    //  This function will read in robot attributes from a file formatted like this:
    //      name x-coord y-coord
    //      R2D2 0 0
    //      C3PO 5 3
    //  - We have already defined variables for the robot name and coordinates above
    //  - Read attributes from file with the stream into these variables
    ////////////////////////////////////////////////////////////
    // YOUR CODE HERE:
    robotStream >> name >> x >> y;

    if (robotStream.fail()) {
        return nullopt;
    }
    ////////////////////////////////////////////////////////////
    // TODO (Question 3, continued):
    //  - Initialize a new Robot with the values you read in
    //  - Instead of nullopt, return the new Robot instead
    ////////////////////////////////////////////////////////////
    // YOUR CODE HERE:
    return Robot(name, x, y, maxDimension);
}

void createRobotsFromFile(vector<Robot>& robots, int maxDimension) {
    string robotsFileName;
    cout << "Enter file name containing the robot definitions: ";
    getline(cin, robotsFileName);
    if (robotsFileName.empty()) {
        robotsFileName = "robots.txt";
    }
    ifstream robotsStream(robotsFileName);
    if (!robotsStream.is_open()) {
        cout << "Could not open robots file: " << robotsFileName << endl;
        exit(-1);
    }

    optional<Robot> possibleRobot;
    do {
        possibleRobot = createRobotFromStream(robotsStream, maxDimension);
        if (possibleRobot.has_value()) {
            robots.push_back(possibleRobot.value());
        }
    } while (possibleRobot.has_value());
    cout << "I read " << robots.size() << " robots from the file" << endl;
}

char getPositionChar(vector<Robot>& robots, int x, int y) {
    char positionChar = '_';
    ////////////////////////////////////////////////////////////
    // TODO (Question 5B):
    //  This function will return the correct character to display at x, y
    //  - If the position is empty, return '_' (default)
    //  - If one robot is at the position, print the first letter of its name
    //  - If more than one robot is at a position, print '*'
    ////////////////////////////////////////////////////////////
    // YOUR CODE HERE:
    

    ////////////////////////////////////////////////////////////
    // Return the position character below
    ////////////////////////////////////////////////////////////
    int robotsHere = 0;
    for (Robot& robot : robots) {
        if (robot.atPosition(x, y)) {
            robotsHere++;
            if (robotsHere == 1) {
                positionChar = robot.getName()[0];
            } else {
                positionChar = '*';
            }
        }
    }
    return positionChar;
}

// Loop over robots at the end of each loop to get the dimensions of the world
// print out the world in ASCII with the first letter of the robot at the right position
// If two robots are there print out an asterisk
// If the position in empty print out an underscore
void printWorld(vector<Robot>& robots, int squareSize) {
    ////////////////////////////////////////////////////////////
    // TODO (Question 5A):
    //  This function will display the correct character at each position
    //  - Iterate over the rows and columns of the board
    //  - Use the function getPositionChar (problem 5B), which returns 
    //      the correct character at each position. 
    //  - Print the board (see example in the writeup)
    ////////////////////////////////////////////////////////////
    // YOUR CODE HERE:
    for (int row = squareSize - 1; row >= 0; row--) {
        for (int col = 0; col < squareSize; col++) {
            cout << getPositionChar(robots, col, row) << " ";
        }
        cout << endl;
    }
}

int main() {
    int MAX_BOUND = 10; // world is always square, so MAX_BOUND x MAX_BOUND

    vector<Robot> robots;
    createRobotsFromFile(robots, MAX_BOUND);

    int numberOfTurns;
    cout << "How many turns do you want to run? ";
    cin >> numberOfTurns;

    int printEvery;
    cout << "Print the world every how many turns? ";
    cin >> printEvery;
    if (printEvery < 1) {
        printEvery = 1;
    }

    for (int turnNumber = 1; turnNumber <= numberOfTurns; turnNumber++) {
        for (Robot& robot: robots) {
            ////////////////////////////////////////////////////////////
            // TODO (Question 4A-B):
            //  This loop iterates over each Robot robot in the vector robots
            //  - Complete the member function makeRandomMove in Robot.cpp
            ////////////////////////////////////////////////////////////
            robot.makeRandomMove();
        }

        ////////////////////////////////////////////////////////////
        // TODO (Question 4C):
        //  Check for a collision!
        //  - Iterate over all Robots in the vector robots
        //  - Compare the position of Robot i to that of every other Robot j by looping again
        //  - Be careful! there is no collision between Robots i and j when i == j
        //  - Print the following statement and then the world when there is a collision:
        //      cout << "Collision! " << r1.getName() << " collided with " << r2.getName() << endl;
        //      printWorld(robots, MAX_BOUND);
        ////////////////////////////////////////////////////////////
        // YOUR CODE HERE:

        
        for (int i = 0; i < (int)robots.size(); i++) {
            for (int j = i + 1; j < (int)robots.size(); j++) {
                if (robots[i].atPosition(robots[j].getX(), robots[j].getY())) {
                    cout << "Collision! " << robots[i].getName() << " collided with " << robots[j].getName() << endl;
                    printWorld(robots, MAX_BOUND);
                }
            }
        }
        // END Question 4.

        ////////////////////////////////////////////////////////////
        // TODO (Question 6 -- EXTRA CREDIT!):
        //  Change this loop to print the status and world map only every N turns.
        ////////////////////////////////////////////////////////////
        if (turnNumber % printEvery == 0 || turnNumber == numberOfTurns) {
            for (Robot& robot: robots) {
                robot.printStatus();
            }
            printWorld(robots, MAX_BOUND);
        }
        
    }
    
    return 0;
}
