/********************************** 
Name: Jeffrey Kersh
Class: CS 121, Spring 2020
Assignment: PA8
Description: Program that simulates battleship and writes statistics to a log file.
Alternates turns between the user and a simulated second player. 
Notes: Sources include lectures by Daniel Olivares, slides posted on canvas, and zybooks
**********************************/

#include "Kersh_PA8.h"

//Function Definitions
/**************************************************************************
Function: welcomeScreen
Date Created: 4/14/2020
Last Modified: 4/14/2020
Description: displays the rules of battleship
Input Parameters: none
Returns: none
Pre: 
Post: prints rules
**************************************************************************/
void welcomeScreen() {
	cout << "***** Welcome to Battleship! *****" << endl;
	cout << endl;
	cout << "Rules of the Game: "<< endl;
	cout << endl;
	cout << "1. This is a two player game." << endl;
	cout << "2. Player1 is you and Player2 is the computer." << endl;
	cout << "3. Place your ships manually, or allow them to be placed randomly. The ships can be placed in any horizontal or vertical position, but not diagonally. Ships cannot overlap with each other or move once the game has begun." << endl;
	cout << "4. A Player will be randomly chosen to go first." << endl;
	cout << "5. Players may call one shot per turn, and the turns alternate back and forth between the two players." << endl;
	cout << "6. On your turn you will enter the cell on the opponent's board that you wish to shoot at. You will be notified if it was a hit or a miss. In the event that it is a hit, you get another opportunity to shoot." << endl;
	cout << "7. Once a player's ship has been hit in each cell that it occupies, the other player will be notified which ship they have sunk." << endl;
	cout << "8. The first player to sink all 5 of their opponent's ships is the winner." << endl;
	cout << endl;
	
}

/**************************************************************************
Function: fillArray
Date Created: 
Last Modified: 4/14/2020
Description: fills an array with '~'
Input Parameters: player grid, number of rows and columns
Returns: none
**************************************************************************/
void fillArray(char arr[NUM_ROWS][NUM_COLS], int rows, int cols) {
	int i, j;
	
	// outer loop iterates over each row
	for (i = 0; i < rows; i++) {
		// inner loop iterates over int in arr[i] (row)
		for (j = 0; j < cols; j++) {
			arr[i][j] = '~';
		}
	}
}

/**************************************************************************
Function: selectWhoStarts
Date Created: 4/14/2020
Last Modified: 4/14/2020
Description: selects who starts
Input Parameters: none
Returns: true if player 1 goes first, false if player 2 goes first
**************************************************************************/
bool selectWhoStarts() {
	int first;
	bool player;
	
	first = rand() % 2;
	
	if (first == 0) {
		cout << "Player1 will go first." << endl;
		player = true;
	}
	else if (first == 1) {
		cout << "Player2 will go first." << endl;
		player = false;
	}
	
	return player;
}

/**************************************************************************
Function: placeUserShips
Date Created: 4/14/2020
Last Modified: 4/16/2020
Description: lets the user choose how they would like to place their ships
Input Parameters: player grid
Returns: none
**************************************************************************/
void placeUserShips(char playerGrid[NUM_ROWS][NUM_COLS]) {
	bool validOption = true;
	int shipPlacementType;
	
	do { 
		cout << "Please select from the following menu:" << endl;
		cout << "1. Enter positions of ships manually." << endl;
		cout << "2. Allow the program to randomly select positions of ships." << endl;
		cin >> shipPlacementType;
	
		if (shipPlacementType == 1) {
			manuallyPlaceShips(playerGrid);
		}
		else if (shipPlacementType == 2) {
			randomlyPlaceShips(playerGrid);
		}
		else {
			cout << "Invalid option! Please try again with a valid option..." << endl;
			validOption = false;
		} 
	} while (validOption == false);
}

/**************************************************************************
Function: manuallyPlaceShips
Date Created: 4/14/2020
Last Modified: 4/17/2020
Description: lets the user manually place ships
Input Parameters: player grid
Returns: none
**************************************************************************/
void manuallyPlaceShips(char playerGrid[NUM_ROWS][NUM_COLS]) {
	int i, j, row, col, direction;
	bool overlap;
	
	for (j = 0; j < 5; ++j) {
		cout << "Please enter the initial row and column for placing your " << shipNames[j] << ". You will then be prompted for the direction." << endl;
	
		do {
		overlap = false;
		cout << "row:";
		cin >> row;
		cout << "col:";
		cin >> col;
		cout << "Please enter the direction. (0-up, 1-right, 2-down, 3-left)" << endl;
		cin >> direction; // 0 - up, 1 - right, 2 - down, 3 - left

		//4 cases - one for each direction
		if (direction == 0) {
			for (i = 0; i < shipSizes[j]; ++i) {
				//checks for ship overlaps
				if (playerGrid[row][col] != '~') {
					overlap = true; 
					cout << "The ship will either end up out of bounds or overlap with another ship...try again." << endl;
					break;
				}
				row--;
			}
			row = row + shipSizes[j];
			for (i = 0; i < shipSizes[j]; ++i) {
				if (overlap == true) {
					break;
				}
				else {
					playerGrid[row--][col] = shipSymbols[j];
				}
			}
		}
		if (direction == 1) {
			for (i = 0; i < shipSizes[j]; ++i) {
				if (playerGrid[row][col] != '~') {
					overlap = true; 
					cout << "The ship will either end up out of bounds or overlap with another ship...try again." << endl;
					break;
				}
				col++;
			}
			col = col - shipSizes[j];
			for (i = 0; i < shipSizes[j]; ++i) {
				if (overlap == true) {
					break;
				}
				else {
					playerGrid[row][col++] = shipSymbols[j];
				}
			}
		}
		
		if (direction == 2) {
			for (i = 0; i < shipSizes[j]; ++i) {
				if (playerGrid[row][col] != '~') {
					overlap = true; 
					cout << "The ship will either end up out of bounds or overlap with another ship...try again." << endl;
					break;
				}
				row++;
			}
			row = row - shipSizes[j];
			for (i = 0; i < shipSizes[j]; ++i) {
				if (overlap == true) {
					break;
				}
				else {
					playerGrid[row++][col] = shipSymbols[j];
				}
			}
		} 
		if (direction == 3) {
			for (i = 0; i < shipSizes[j]; ++i) {
				if (playerGrid[row][col] != '~') {
					overlap = true;
					cout << "The ship will either end up out of bounds or overlap with another ship...try again." << endl;
					 break;
				}
				col--;
			}
			col = col + shipSizes[j];
			for (i = 0; i < shipSizes[j]; ++i) {
				if (overlap == true) {
					break;
				}
				else {
					playerGrid[row][col--] = shipSymbols[j];
				}
			}
		}
		} while (overlap == true);
	
	
	}
}

/**************************************************************************
Function: randomlyPlaceSingleShip
Date Created: 4/14/2020
Last Modified: 4/16/2020
Description: randomly places one ship
Input Parameters: player grid, name of ship, symbol of ship, size of ship
Returns: none
**************************************************************************/
void randomlyPlaceSingleShip(char playerGrid[NUM_ROWS][NUM_COLS], int name, int symbol, int size) {
	int row, col, direction, i;
	bool overlap;

	do {
	overlap = false;
	row = rand() % 10;
	col = rand() % 10;
	direction = rand() % 4; // 0 - up, 1 - right, 2 - down, 3 - left

	//prevent ships from going over the side of the board
	if (row < shipSizes[size]) { 
		direction = 2;
	} 
	if (9 - col < shipSizes[size]) {
		direction = 3;
	}
	if (9 - row < shipSizes[size]) {
		direction = 0;
	}
	if (col < shipSizes[size]) {
		direction = 1;
	} 
	
	//4 cases - one for each direction that is randomly selected
	if (direction == 0) {
		for (i = 0; i < shipSizes[size]; ++i) {
			//checks for ship overlaps
			if (playerGrid[row][col] != '~') {
				overlap = true; break;
			}
			row--;
		}
		row = row + shipSizes[size];
		for (i = 0; i < shipSizes[size]; ++i) {
			if (overlap == true) {
				break;
			}
			else {
				playerGrid[row--][col] = shipSymbols[symbol];
			}
		}
	}
	if (direction == 1) {
		for (i = 0; i < shipSizes[size]; ++i) {
			if (playerGrid[row][col] != '~') {
				overlap = true; break;
			}
			col++;
		}
		col = col - shipSizes[size];
		for (i = 0; i < shipSizes[size]; ++i) {
			if (overlap == true) {
				break;
			}
			else {
				playerGrid[row][col++] = shipSymbols[symbol];
			}
		}
	}
	if (direction == 2) {
		for (i = 0; i < shipSizes[size]; ++i) {
			if (playerGrid[row][col] != '~') {
				overlap = true; break;
			}
			row++;
		}
		row = row - shipSizes[size];
		for (i = 0; i < shipSizes[size]; ++i) {
			if (overlap == true) {
				break;
			}
			else {
				playerGrid[row++][col] = shipSymbols[symbol];
			}
		}
	} 
	if (direction == 3) {
		for (i = 0; i < shipSizes[size]; ++i) {
			if (playerGrid[row][col] != '~') {
				overlap = true; break;
			}
			col--;
		}
		col = col + shipSizes[size];
		for (i = 0; i < shipSizes[size]; ++i) {
			if (overlap == true) {
				break;
			}
			else {
				playerGrid[row][col--] = shipSymbols[symbol];
			}
		}
	}
	} while (overlap == true);
}

/**************************************************************************
Function: randomlyPlaceShips
Date Created: 4/14/2020
Last Modified: 4/15/2020
Description: randomly places ships
Input Parameters: player grid
Returns: none
**************************************************************************/
void randomlyPlaceShips(char playerGrid[NUM_ROWS][NUM_COLS]) {
	int i;
	// for each ship i in our parallel arrays of ships
	for (i = 0; i < 5; ++i) {
		randomlyPlaceSingleShip(playerGrid, i, i, i);
	}
}

/**************************************************************************
Function: printArray
Date Created: 
Last Modified: 4/14/2020
Description: prints an array
Input Parameters: array, number of rows and columns
Returns: none
**************************************************************************/
void printArray(const char arr[NUM_ROWS][NUM_COLS], int rows, int cols) {
	int i, j;
	
	//label x-axis at the top
	cout << "  0 1 2 3 4 5 6 7 8 9" << endl;
	//print array
	for (i = 0; i < rows; i++) {
		//label y-axis
		cout << i << " ";
		for (j = 0; j < cols; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

/**************************************************************************
Function: enterTarget
Date Created: 4/14/2020
Last Modified: 4/14/2020
Description: prompts the user for a target
Input Parameters: none
Returns: location of the target
**************************************************************************/
int enterTarget() {
	int location;
	bool valid = true;

	cout << "Please enter a target in the form of two integers corresponding to [row][column]: ";
	cin >> location;
	
	return location;
}

/**************************************************************************
Function: checkShot
Date Created: 4/14/2020
Last Modified: 4/16/2020
Description: checks if the shot hit a ship
Input Parameters: player grid, row and column of shot, output file, player number
Returns: character indicating a hit or miss
**************************************************************************/
char checkShot(char playerGrid[NUM_ROWS][NUM_COLS], char displayGrid[NUM_ROWS][NUM_COLS], int row, int column, ofstream& outputFile, int player) {
	char symbol;
	char hit = '*';
	
	if (playerGrid[row][column] != '~') {
		cout << row << "," << column << " was a ...HIT!!!" << endl;
		symbol = playerGrid[row][column];
		displayGrid[row][column] = '*';
		printToLog(outputFile, row, column, hit, player);
	}
	else {
		cout << row << "," << column << " was a miss.." << endl;
		displayGrid[row][column] = 'm';
		symbol = 'm';
		printToLog(outputFile, row, column, symbol, player);
	}
	
	return symbol;
}

/**************************************************************************
Function: checkIfSunk
Date Created: 4/14/2020
Last Modified: 4/16/2020
Description: in the event of a hit, checks if the ship is sunk
Input Parameters: symbol of hit, sunk ship count, player grid, output file
Returns: updates the count of sunk ships
**************************************************************************/
int checkIfSunk(char symbol, int counters[], int sunkShipsCount, char p2SolutionGrid[NUM_ROWS][NUM_COLS], char p2DisplayGrid[NUM_ROWS][NUM_COLS], ofstream& outputFile) {
	int i;
	
	//find out which ship was hit
	for (i = 0; i < 5; ++i) {
		if (symbol == shipSymbols[i]) {
			counters[i] -= 1;
			if (counters[i] == 0) {
				sunkShipsCount += 1;
				cout << shipNames[i] << " was sunk!!!" << endl;
				//write to log file that it was sunk
				outputFile << "ship sunk" << endl;
				//update display grid with proper letters
				updateBoard(p2SolutionGrid, p2DisplayGrid, symbol);
			}
			else {
				outputFile << "not sunk" << endl;
			}
		}
	}	
			
	return sunkShipsCount;
}

/**************************************************************************
Function: isWinner
Date Created: 4/14/2020
Last Modified: 4/17/2020
Description: determines if there is a winner
Input Parameters: sunk ships count for each player
Returns: true if there is a winner, false if there is not yet a winner
**************************************************************************/
bool isWinner(int p1sunkShipsCount, int p2sunkShipsCount) {
	bool winner;
	
	if (p1sunkShipsCount < 5 && p2sunkShipsCount < 5) {
		winner = false;
	}
	else if (p1sunkShipsCount >= 5) {
		winner = true;
		cout << "You Won! Congratulations!" << endl;
	}
	else {
		winner = true;
		cout << "Player 2 won..." << endl;
	}
	
	return winner;
}

/**************************************************************************
Function: updateBoard
Date Created: 4/14/2020
Last Modified: 4/14/2020
Description: updates the board with the status of a hit
Input Parameters: player boards, symbol of hit
Returns: none
**************************************************************************/
void updateBoard(char playerGrid[NUM_ROWS][NUM_COLS], char displayGrid[NUM_ROWS][NUM_COLS], char symbol) {
	int i, j;
	for (i = 0; i < NUM_ROWS; ++i) {
		for (j = 0; j < NUM_COLS; ++j) {
			if (symbol == playerGrid[i][j]) {
				displayGrid[i][j] = symbol;
			}
		}
	}
}

/**************************************************************************
Function: clearScreen
Date Created: 4/15/2020
Last Modified: 4/15/2020
Description: clears console
Input Parameters: none
Returns: none
**************************************************************************/
void clearScreen() { 
	cout << "Press enter to continue...\n";
	//cin.ignore();
	cin.get(); 
	system("clear");
}

/**************************************************************************
Function: openFile
Date Created: 4/16/2020
Last Modified: 4/16/2020
Description: opens log file
Input Parameters: log file
Returns: none
**************************************************************************/
void openFile(ofstream& outputFile) {
	outputFile.open("battleship.log");
	if (outputFile.is_open()) {
		cout << "Writing data to battleship.log" << endl;
	}
	else {
		cout << "Failed to open output file..." << endl;
		exit (-1);
	}
}

/**************************************************************************
Function: closeFile
Date Created: 4/16/2020
Last Modified: 4/16/2020
Description: closes log file
Input Parameters: log file
Returns: none
**************************************************************************/
void closeFile(ofstream& outputFile) {
	outputFile.close();
	if (outputFile.is_open()) {
		cout << "Failed to close battleship.log..." << endl;
		}
		else {
			cout << "Closing battleship.log..." << endl;
		}
}

/**************************************************************************
Function: printToLog
Date Created: 4/17/2020
Last Modified: 4/17/2020
Description: writes information to log file
Input Parameters: row, column, whether the shot was a hit or miss, which player's turn
Returns: none
**************************************************************************/
void printToLog(ofstream& outputFile, int row, int column, char hit, int player) {
	outputFile << player << " " << row << column << " " << hit << " ";
}

/**************************************************************************
Function: outputStats
Date Created: 4/17/2020
Last Modified: 4/17/2020
Description: calculates statistics and writes them to log file
Input Parameters: number of hits, misses, which player they correspond to, who won
Returns: none
**************************************************************************/
void outputStats(ofstream& outputFile, int player, int hits, int misses, int winner) {
	int total;
	double ratio;
	string outcome;
	
	total = hits + misses;
	ratio = static_cast<double>(hits) / static_cast<double>(misses) * 100;

	if (player == winner) {
		outcome = "Winner";
	}
	else {
		outcome = "Loser";
	}
	
	outputFile << endl;
	outputFile << "Player " << player << " Statistics" << endl;
	outputFile << "Total Hits: " << hits << endl;
	outputFile << "Total Misses: " << misses << endl;
	outputFile << "Total Shots: " << total << endl;
	outputFile << "Ratio of hits to misses: " << ratio << "%" << endl;
	outputFile << "Outcome: " << outcome << endl;
	outputFile << endl;
	
}

