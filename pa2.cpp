#include <iostream>
#include <cstring>
#include "cleaning_robot.h"
using namespace std;

/*
   *    COMP 2011 2021 Fall Programming Assignment 2
   *    Student Name        : OH, Jintaek
   *    Student ID          : 20554393
   *    Student ITSC email  : johaa@connect.ust.hk
   * 
   * You are not allowed to use extra library
*/

// Please do all your work in this file. You just need to submit this file.
int sensor(char map[MAP_HEIGHT][MAP_WIDTH], int x, int y)
{
    int result = 0; // by default
    
    if (x <= MAP_WIDTH && y <= MAP_HEIGHT){
        if (map[y][x] == ' '){
            result = 0;  // Available
        }
        else if (map[y][x] == 'B'){
            result = 1; // Blocked
        }
        else if (map[y][x] == 'R'){
            result = 2; // Robot
        }
        else if (map[y][x] == 'C'){
            result = 3; // Charger
        }
        else if (map[y][x] == 'V'){
            result = 4; // Visited
        }
        return result;
    }
    else {return -1;}
}

void marking(char result_map[MAP_HEIGHT][MAP_WIDTH], int x, int y)
{
    result_map[y][x] = 'V';
}

int min(int x, int y)
{
    if (x > y){return y;}
    else if (x < y){return x;}
    else {return x;}
}

int findMaximumPlace(int robot_x, int robot_y, int robot_energy, int robot_full_energy, char result_map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{
    int status = sensor(result_map, robot_x, robot_y);
    
    if (robot_y >= MAP_HEIGHT || robot_x >= MAP_WIDTH || robot_x < 0 || robot_y < 0 ||robot_energy < 0 || status == 1){return 0;}
    
    if (status == 3){robot_energy = robot_full_energy;}
    
    if (sensor(result_map, robot_x, robot_y) == 4){
        return findMaximumPlace(robot_x, robot_y-1, robot_energy-1, robot_full_energy, result_map, temp_map)+findMaximumPlace(robot_x+1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map)+findMaximumPlace(robot_x, robot_y+1, robot_energy-1, robot_full_energy, result_map, temp_map)+findMaximumPlace(robot_x-1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map);
    }
    
    marking(result_map, robot_x, robot_y);
    
    return 1 +findMaximumPlace(robot_x, robot_y-1, robot_energy-1, robot_full_energy, result_map, temp_map)+findMaximumPlace(robot_x+1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map)+findMaximumPlace(robot_x, robot_y+1, robot_energy-1, robot_full_energy, result_map, temp_map)+findMaximumPlace(robot_x-1, robot_y, robot_energy-1, robot_full_energy, result_map, temp_map);
}

int findShortestDistance(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{
    if (temp_map[0][0] == '\0'){
        copyMap (temp_map, map);
        }
    
    int status = sensor(temp_map, robot_x, robot_y);

    if (robot_y >= MAP_HEIGHT || robot_x >= MAP_WIDTH || robot_x < 0 || robot_y < 0 || robot_energy < 0 || status == 1){
        return PA2_MAX_PATH;
        }
        
    if (robot_x == target_x && robot_y == target_y){
        return 1;
        }

    if (status == 3) {
        robot_energy = robot_full_energy;
        temp_map[robot_y][robot_x] = AVAILABLE;
        }
    
    char temp_map2[MAP_HEIGHT][MAP_WIDTH];
    
    copyMap(temp_map2, temp_map);
    int up = findShortestDistance(robot_x, robot_y-1, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map2);
    
    copyMap(temp_map2, temp_map);
    int right = findShortestDistance(robot_x+1, robot_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map2);
    
    copyMap(temp_map2, temp_map);
    int down = findShortestDistance(robot_x, robot_y+1, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map2);
    
    copyMap(temp_map2, temp_map);
    int left  =findShortestDistance(robot_x-1, robot_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map2);
        
    return 1 + min (up, min (right, min (down,left)));

}

int findFarthestPossibleCharger(int robot_x, int robot_y, int robot_original_x, int robot_original_y, int &target_x, int &target_y, int robot_energy, int robot_full_energy, const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{

    if (temp_map[0][0] == '\0'){
        copyMap (temp_map, map);
    }
            
    int status = sensor(temp_map, robot_x, robot_y);

    if (robot_y >= MAP_HEIGHT || robot_x >= MAP_WIDTH || robot_x < 0 || robot_y < 0 || robot_energy < 0 || status == 1){
        return PA2_MAX_PATH;
    }
    
    char temp_map2[MAP_HEIGHT][MAP_WIDTH];

    if (status == 3){
        if (target_x == -1 || target_y == -1){
            target_x = robot_x;
            target_y = robot_y;
            temp_map[robot_y][robot_x] = AVAILABLE;
            return 1;
        }
        else if (target_x != -1 || target_y != -1){
            int d1 = findShortestDistance(robot_original_x, robot_original_y, robot_x, robot_y, robot_full_energy, robot_full_energy, map, temp_map);
            int d2 = findShortestDistance(robot_original_x, robot_original_y, target_x, target_y, robot_full_energy, robot_full_energy, map, temp_map);
            if (d1 > d2){
                target_x = robot_x;
                target_y = robot_y;
                temp_map[robot_y][robot_x] = AVAILABLE;
                return 1;
            }
        }
    }
            
    copyMap(temp_map2, temp_map);
    int up = findFarthestPossibleCharger(robot_x, robot_y-1, robot_original_x, robot_original_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
            
    copyMap(temp_map2, temp_map);
    int right = findFarthestPossibleCharger(robot_x+1, robot_y, robot_original_x, robot_original_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
            
    copyMap(temp_map2, temp_map);
    int down = findFarthestPossibleCharger(robot_x, robot_y+1, robot_original_x, robot_original_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
            
    copyMap(temp_map2, temp_map);
    int left  = findFarthestPossibleCharger(robot_x-1, robot_y, robot_original_x, robot_original_y, target_x, target_y, robot_energy-1, robot_full_energy, map, temp_map);
        
    int result = 1 + min (up, min (right, min (down,left)));
        
    if (result > PA2_MAX_PATH|| findShortestDistance(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, map, temp_map) > PA2_MAX_PATH){
        return -1;
    }
    else{
        return findShortestDistance(robot_x, robot_y, target_x, target_y, robot_energy, robot_full_energy, map, temp_map);
    }
}

int findPathSequence(int robot_x, int robot_y, int target_x, int target_y, int robot_energy, int robot_full_energy, char result_sequence[], const char map[MAP_HEIGHT][MAP_WIDTH], char temp_map[MAP_HEIGHT][MAP_WIDTH])
{
    char empty_result_sequence[MAX_STRING_SIZE] = "";
    
    if (temp_map[0][0] == '\0')
    {
        copyMap (temp_map, map);
        strcpy(result_sequence, empty_result_sequence);
    }
    
    int status = sensor(temp_map, robot_x, robot_y);
    
    if (robot_y >= MAP_HEIGHT || robot_x >= MAP_WIDTH || robot_x < 0 || robot_y < 0 || robot_energy < 0 || status == 1){return PA2_MAX_PATH;}
    
    if (robot_x == target_x && robot_y == target_y){
       result_sequence = strcat(result_sequence,"T");
       return 1;
      }

    if (status == 3) {
       robot_energy = robot_full_energy;
       temp_map[robot_y][robot_x] = AVAILABLE;
      }
    
    char temp_map2[MAP_HEIGHT][MAP_WIDTH];
    char result_sequence1[MAX_STRING_SIZE];
    char result_sequence2[MAX_STRING_SIZE];
    copyMap(temp_map2, temp_map);
    
    strcpy(result_sequence1, result_sequence);
    int up = findPathSequence(robot_x, robot_y-1, target_x, target_y, robot_energy-1, robot_full_energy,strcat(result_sequence1, "U"), map, temp_map2);
    copyMap(temp_map2, temp_map);
    
    strcpy(result_sequence2, result_sequence);
    int right = findPathSequence(robot_x+1, robot_y, target_x, target_y, robot_energy-1, robot_full_energy,strcat(result_sequence2, "R"), map, temp_map2);
    copyMap(temp_map2, temp_map);
    
    if (up > right) {
        strcpy (result_sequence1, result_sequence2);
    }
    
    strcpy(result_sequence2, result_sequence);
    int down = findPathSequence(robot_x, robot_y+1, target_x, target_y, robot_energy-1, robot_full_energy,strcat(result_sequence2, "D"), map, temp_map2);
    copyMap(temp_map2, temp_map);
    
    if (min(up, right) > down) {
        strcpy (result_sequence1, result_sequence2);
    }
    
    strcpy(result_sequence2, result_sequence);
    int left  = findPathSequence(robot_x-1, robot_y, target_x, target_y, robot_energy-1, robot_full_energy,strcat(result_sequence2, "L"), map, temp_map2);
    
    if (min(min(up, right),down) > left) {
       strcpy (result_sequence1, result_sequence2);
    }
    
    strcpy(result_sequence, result_sequence1);
    
    return 1 + min (up, min (right, min (down,left)));
}
