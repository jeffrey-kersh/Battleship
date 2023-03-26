/********************************** 
Name: Jeffrey Kersh
Class: CS 121, Spring 2020
Assignment: PA8
Description: Program that simulates battleship and writes statistics to a log file.
Alternates turns between the user and a simulated second player. 
Notes: Sources include lectures by Daniel Olivares, slides posted on canvas, and zybooks
**********************************/

#ifndef Kersh_PA8_H
#define Kersh_PA8_H

//includes
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<ctime>

//namespace
using namespace std;

//constant global variables
const int NUM_ROWS = 10;
const int NUM_COLS = 10;
// lets store ship info in 3 parallel arrays
const string shipNames[] = {"carrier", "battleship", "cruiser", "submarine", "destroyer"};
const char shipSymbols[] = {'c', 'b', 'r', 's', 'd'};
const int shipSizes[] = {5, 4, 3, 3, 2};

//Function Protoypes
void welcomeScreen();
void fillArray(char[NUM_ROWS][NUM_COLS], int, int);
bool selectWhoStarts();
void placeUserShips(char[NUM_ROWS][NUM_COLS]);
void manuallyPlaceShips(char[NUM_ROWS][NUM_COLS]);
void randomlyPlaceShips(char[NUM_ROWS][NUM_COLS]);
void randomlyPlaceSingleShip(char[NUM_ROWS][NUM_COLS], int, int, int);
void checkForOverlap();
void printArray(const char[NUM_ROWS][NUM_COLS], int, int);
int enterTarget();
char checkShot(char[NUM_ROWS][NUM_COLS], char[NUM_ROWS][NUM_COLS], int, int, ofstream&, int);
int checkIfSunk(char, int[], int, char[NUM_ROWS][NUM_COLS], char[NUM_ROWS][NUM_COLS], ofstream&);
bool isWinner(int, int);
void updateBoard(char[NUM_ROWS][NUM_COLS], char[NUM_ROWS][NUM_COLS], char);
void outputStats(ofstream&, int, int, int, int);
void clearScreen();
void openFile(ofstream&);
void closeFile(ofstream&);
void printToLog(ofstream&, int, int, char, int);

#endif

