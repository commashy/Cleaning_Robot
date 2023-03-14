# Cleaning_Robot
 This repository contains the source code for a cleaning robot implemented in C++ as part of the COMP 2011 (Programming for Scientists and Engineers I) course at HKUST.

The cleaning robot is capable of navigating a given map, which is represented as a 2D array of characters. The robot can move in four directions (up, right, down, and left), and it has a limited amount of energy that is consumed with each movement. The robot can also recharge itself by locating and moving to a special cell on the map designated as a charger.

The code includes several functions that implement the robot's behavior, such as:

- **`sensor()`**: returns information about the cell the robot is currently located in (e.g., whether it's empty, blocked, or contains a charger).
- **`marking()`**: marks a cell on the map as visited by the robot.
- **`findMaximumPlace()`**: calculates the maximum number of cells the robot can visit starting from its current position and with its current energy level.
- **`findShortestDistance()`**: calculates the shortest distance between the robot's current position and a target position on the map.
- **`findFarthestPossibleCharger()`**: finds the farthest reachable charger cell from the robot's current position.

The code is well-commented and includes a header file **`cleaning_robot.h`** that defines constants and function prototypes.

## **Usage**

To use the cleaning robot, simply include the **`cleaning_robot.h`** header file and call the appropriate functions with the relevant parameters. The robot's behavior is based on the given map, so make sure to provide a valid map as input.
