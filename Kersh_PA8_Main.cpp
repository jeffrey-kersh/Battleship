/********************************** 
Name: Jeffrey Kersh
Class: CS 121, Spring 2020
Assignment: PA8
Description: Program that simulates battleship and writes statistics to a log file.
Alternates turns between the user and a simulated second player. 
Notes: Sources include lectures by Daniel Olivares, slides posted on canvas, and zybooks
**********************************/

#include "Kersh_PA8.h"

int main() {
	//Variable Declaration Block etc.
	char p1SolutionGrid[NUM_ROWS][NUM_COLS]; // 10 x 10 chars for user
	char p2SolutionGrid[NUM_ROWS][NUM_COLS]; // 10 x 10 chars for computer
	char p2DisplayGrid[NUM_ROWS][NUM_COLS]; // 10 x 10 chars for computer Display
	int i = 0, location, row, column, hit, won, p1sunkShipsCount = 0, p2sunkShipsCount = 0, p1hits = 0, p2hits = 0, p1misses = 0, p2misses = 0; 
	char symbol;
	int counters[] = {5, 4, 3, 3, 2};
	int p2counters[] = {5, 4, 3, 3, 2};
	bool starter, flag;
	ofstream outputFile;
	srand(time(0));
	
	
	//#1 Display Rules
	welcomeScreen();
	
	//#2 fill user & computer arrays with '-'
	fillArray(p1SolutionGrid, NUM_ROWS, NUM_COLS); 
	fillArray(p2SolutionGrid, NUM_ROWS, NUM_COLS); 
	fillArray(p2DisplayGrid, NUM_ROWS, NUM_COLS);
	
	clearScreen();
	
	//#3 manually place user's ships or randomly place user's ships
	placeUserShips(p1SolutionGrid); 
	
	//#4 randomly place computer's ships
	randomlyPlaceShips(p2SolutionGrid); 
	
	//#5 determine which player goes first
	starter = selectWhoStarts();
	
	//open log file
	openFile(outputFile);
	do {
		//if true - player 1 goes first
		if (starter == true) {
			//#6 display board
			cout << "******** Your Board ********" << endl;
			printArray(p1SolutionGrid, NUM_ROWS, NUM_COLS);
			cout << "******** Computer's Board ********" << endl;
			printArray(p2DisplayGrid, NUM_ROWS, NUM_COLS); 
		
			//#7 enter a target
			location = enterTarget();
				column = location % 10;
				row = (location - column) / 10;
				//to do: validate that target has not been picked before
			
			//Clear Screen
			clearScreen();
	
			//#8 check for hit or miss
			symbol = checkShot(p2SolutionGrid, p2DisplayGrid, row, column, outputFile, 1);
				//row, column, hit status are written to log file here
			if (symbol != '~' && symbol  != 'm') {
				p1sunkShipsCount = checkIfSunk(symbol, counters, p1sunkShipsCount, p2SolutionGrid, p2DisplayGrid, outputFile); 
					//#9 check if ship is sunk
					//#10 update board is called within this function
				p1hits += 1;
			}
			else {
				outputFile << "not sunk" << endl;
				p1misses += 1;
				starter = false;
			}
		}
		//if false - player 2 goes first
		if (starter == false) {
			//#6 display board
			cout << "******** Your Board ********" << endl;
			printArray(p1SolutionGrid, NUM_ROWS, NUM_COLS);
			cout << "******** Computer's Board ********" << endl;
			printArray(p2DisplayGrid, NUM_ROWS, NUM_COLS); 
		
			//#7 enter a target
				location = rand() % 100;
				column = location % 10;
				row = (location - column) / 10;
				//to do: validate that target has not been picked before
			
			//Clear Screen
			clearScreen();
			
			cout << "Computer selects " << row << ", " << column << "!" << endl;
	
			//#8 check for hit or miss
			symbol = checkShot(p1SolutionGrid, p1SolutionGrid, row, column, outputFile, 2);
			if (symbol != '~' && symbol != 'm') {
				p2sunkShipsCount = checkIfSunk(symbol, p2counters, p2sunkShipsCount, p1SolutionGrid, p1SolutionGrid, outputFile); 
					//#9 check if ship is sunk
					//#10 update board is called within this function
				p2hits += 1;
			}
			else {
				outputFile << "not sunk" << endl;
				p2misses += 1;
				starter = true;
			}
		}
	} while (isWinner(p1sunkShipsCount, p2sunkShipsCount) == false);
	
	cout << "********* Final Board Positions *********" << endl;
	cout << "You:";
	printArray(p1SolutionGrid, NUM_ROWS, NUM_COLS);
	cout << "Computer:";
	printArray(p2SolutionGrid, NUM_ROWS, NUM_COLS);
	
	//determine variable 'won' to pass to the statistics file
	if (p2sunkShipsCount >=5) {
		won = 2;
	}
	if (p1sunkShipsCount >= 5) {
		won = 1;
	}
	
	//#11 write statistics to the log file
	outputStats(outputFile, 1, p1hits, p1misses, won); 
	outputStats(outputFile, 2, p2hits, p2misses, won);
	
	//close log file
	closeFile(outputFile);
	
	return 0;
}

