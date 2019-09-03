#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

// function prototype
void menuArt();
bool validStart(char start[]);
void gotoxy(int x, int y);
bool gridCheck(int grid[4][4]);
bool duplicateCheck(int array[4][4], int array2[4][4]);

int main()
{
	// int variable
	int i, j, k;
	int repeat;
	int temp1, temp2;
	int highScore, score;
	int grid[4][4], grid2[4][4];
	int choice;
	int maxNumber;
	
	// char variable
	char start[10];
	char input;
	
	// boolean flag
	bool gameOverFlag = false;
	bool continueFlag = false;
	bool emptySpace = false;
	bool validInput = false;
	
	// file pointers
	FILE *data = NULL;
	
	do
	{
		// display title screen
		menuArt();
		gameOverFlag = false;
		continueFlag = false;
		score = 0;
		
		// access and read score data
		data = fopen("score.owen", "rb");
		//fwrite (&highScore, sizeof(highScore), 1, data);
		fread(&highScore, sizeof(highScore), 1, data);
		if (data == NULL)
		{
			highScore = 0;
			printf("Data 'score.owen' not found and will be created after game over\n\n");
		}
		printf("Best Score: %d\n", highScore);
		fclose(data);
		
		// display menu
		printf("1. Play!\n");
		printf("2. Instruction\n");
		printf("3. Exit\n");
		
		// prompt user choice input
		do
		{
			choice = 0;
			printf("Choice: ");
			scanf("%d", &choice);
			fflush(stdin);
		}
		while ((choice != 1 && choice != 2 && choice != 3));
		
		if (choice == 1 && gameOverFlag == false)
		{
			puts("");
			
			// prompt user to start game
			do
			{
				strcpy(start, "\n");
				printf("Please type 'Start Game' to begin: ");
				scanf("%[^\n]s", start);
				fflush(stdin);
			}
			while(validStart(start) == false);
			
			// initialize blank grid
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
					grid[i][j] = 0;
					
			
			srand(time(NULL));
			temp1 = 4;
			temp2 = 4;
			maxNumber = 0;
			
			// generate first two numbers in random spots on grid
			for (k = 0; k < 2; k++)
			{
				do
				{
					i = rand() % 4;
					j = rand() % 4;
				}
				while (i == temp1 && j == temp2);
				
				temp1 = i;
				temp2 = j;
				grid[i][j] = rand() % 100;
				
				if (grid[i][j] < 90)
					grid[i][j] = 2;
				else
					grid[i][j] = 4;
			}
			
			do
			{
				system("cls");
				
				// display game interface
				menuArt();
				printf("Score : %7d        | Best Score : %7d\n", score, highScore);
				printf("\n\n");
				
				// display current grid
				for (i = 0; i < 4; i++)
				{
					printf("     |");
					for (j = 0; j < 4; j++)
					{
						if (grid[i][j] != 0)
							printf(" %4d   |", grid[i][j]);
						else
							printf(" %4c   |", ' ');
					}
					printf("\n\n");
				}
				
				// display game over screen
				if (gridCheck(grid) == false)
				{
					printf("\nG A M E  O V E R");
					printf("\n=============================");
					printf("\nFinal Score : %d", score);
					printf("\nPrevious Best Score : %d", highScore);
					gameOverFlag = true;
					continueFlag = false;
					
					// access and overwrite new high score on score data
					if (score > highScore)
					{
						printf("\n\nCONGRATULATION!!");
						printf("\nNEW PERSONAL RECORD");
						highScore = score;
						
						data = fopen("score.owen", "wb");
						fwrite (&highScore, sizeof (highScore), 1, data);
						fclose(data);
					}
					else if (score == 0 && data == NULL) // if score is 0 and no score data exist
					{
						data = fopen("score.owen", "wb");
						fwrite(&score, sizeof (score), 1, data);
						fclose(data);
					}
					
					printf("\nPress 'Enter' to continue");
					
					getchar();
					system("cls");
				}
				
				// display victory screen when highest number reached 2048
				if (maxNumber == 2048 && continueFlag == false)
				{
					printf("\nYOU WON THE GAME!!\n");
					
					// prompt user for continuation input
					do
					{
						printf("Continue[y/n] : ");			
						scanf("%c", &input);
						fflush(stdin);
					}
					while (input != 'y' && input != 'n');
					
					// display game over screen
					if (input == 'n')
					{
						printf("\nG A M E  O V E R");
						printf("\n=============================");
						printf("\nFinal Score : %d", score);
						printf("\nPrevious Best Score : %d", highScore);
						gameOverFlag = true;
						continueFlag = false;
						
						// access and overwrite new high score on score data
						if (score > highScore)
						{
							printf("\n\nCONGRATULATION!!");
							printf("\nNEW PERSONAL RECORD");
							highScore = score;
							
							data = fopen("score.owen", "wb");
							fwrite (&highScore, sizeof (highScore), 1, data);
							fclose(data);
						}
						else if (score == 0 && data == NULL) // if score is 0 and no score data exist
						{
							data = fopen("score.owen", "wb");
							fwrite(&score, sizeof (score), 1, data);
							fclose(data);
						}
						
						printf("\nPress 'Enter' to continue");
						
						getchar();
						system("cls");
					}
					else if (input == 'y') // if user continue the game
					{
						continueFlag = true;
						
						system("cls");
				
						// display game interface
						menuArt();
						printf("Score : %7d        | Best Score : %7d\n", score, highScore);
						printf("\n\n");
						
						// display current grid
						for (i = 0; i < 4; i++)
						{
							printf("     |");
							for (j = 0; j < 4; j++)
							{
								if (grid[i][j] != 0)
									printf(" %4d   |", grid[i][j]);
								else
									printf(" %4c   |", ' ');
							}
							printf("\n\n");
						}
					}
				}
						
				// break loop and return to title screen
				if (gameOverFlag == true)
					break;
				
				// display control scheme
				gotoxy(10, 23);
				printf("w");
				gotoxy(5, 25);
				printf("a");
				gotoxy(10, 25);
				printf("s");
				gotoxy(15, 25);
				printf("d");
				
				// initialize backup grid for comparison
				for (i = 0; i < 4; i++)
					for (j = 0; j < 4; j++)
						grid2[i][j] = grid[i][j];
				
				// prompt user control input
				gotoxy(0, 20);
				validInput = true;
				printf("\nInput Key : ");
				scanf("%c", &input);
				fflush(stdin);
						
				// move numbers on grid depending on user input
				switch (input)
				{
					case 'a':
						for (repeat = 1; repeat <= 3; repeat++)
							for (i = 0; i < 4; i++)
								for (j = 0; j < 3; j++)
								{
									// if no number found on spot
									if (!grid[i][j] && repeat != 2)
									{
										for (k = j + 1; k < 4; k++)
										{
											if (grid[i][k])
											{
												grid[i][j] = grid[i][k];
												grid[i][k] = 0;
												break;
											}
										}
									}
									else if (grid[i][j] && grid[i][j] == grid[i][j + 1] && repeat == 2) // if two numbers are able to combine
									{
										grid[i][j] += grid[i][j + 1];
										score += grid[i][j];
										if (grid[i][j] > maxNumber)
										{
											maxNumber = grid[i][j];
										}
										grid[i][j + 1] = 0;
									}
								}		
						break;
						
					case 'd':
						for (repeat = 1; repeat <= 3; repeat++)
							for (i = 0; i < 4; i++)
								for (j = 3; j > 0; j--)
								{
									// if no number found on spot
									if (!grid[i][j] && repeat != 2)
									{
										for (k = j - 1; k >= 0; k--)
										{
											if (grid[i][k])
											{
												grid[i][j] = grid[i][k];
												grid[i][k] = 0;
												break;
											}
										}
									}
									else if (grid[i][j] && grid[i][j] == grid[i][j - 1] && repeat == 2) // if two numbers are able to combine
									{
										grid[i][j] += grid[i][j - 1];
										score += grid[i][j];
										if (grid[i][j] > maxNumber)
										{
											maxNumber = grid[i][j];
										}
										grid[i][j - 1] = 0;
									}
								}
						break;
						
					case 'w':
						for (repeat = 1; repeat <= 3; repeat++)
							for (i = 0; i < 4; i++)
								for (j = 0; j < 3; j++)
								{
									// if no number found on spot
									if (!grid[j][i] && repeat != 2)
									{
										for (k = j + 1; k < 4; k++)
										{
											if (grid[k][i])
											{
												grid[j][i] = grid[k][i];
												grid[k][i] = 0;
												break;
											}
										}
									}
									else if (grid[j][i] && grid[j][i] == grid[j + 1][i] && repeat == 2) // if two numbers are able to combine
									{
										grid[j][i] += grid[j + 1][i];
										score += grid[j][i];
										if (grid[j][i] > maxNumber)
										{
											maxNumber = grid[j][i];
										}
										grid[j + 1][i] = 0;
									}
								}
						break;
					
					case 's':
						for (repeat = 1; repeat <= 3; repeat++)
							for (i = 0; i < 4; i++)
								for (j = 3; j > 0; j--)
								{
									// if no number found on spot
									if (!grid[j][i] && repeat != 2)
									{
										for (k = j - 1; k >= 0; k--)
										{
											if (grid[k][i])
											{
												grid[j][i] = grid[k][i];
												grid[k][i] = 0;
												break;
											}
										}
									}
									else if (grid[j][i] && grid[j][i] == grid[j - 1][i] && repeat == 2) // if two numbers are able to combine
									{
										grid[j][i] += grid[j - 1][i];
										score += grid[j][i];
										if (grid[j][i] > maxNumber)
										{
											maxNumber = grid[j][i];
										}
										grid[j - 1][i] = 0;
									}
								}
						break;
						
					default:
						// if user input is false
						validInput = false;
						break;
				}
				
				// check if an empty space exist on grid
				emptySpace = false;
				for (i = 0; i < 4; i++)
					for (j = 0; j < 4; j++)
						if (!grid[i][j])
							emptySpace = true;
				
				// if empty space exist and grid numbers has been moved
				if (emptySpace == true && duplicateCheck(grid, grid2) == true && validInput == true)
				{
					do
					{
						i = rand() % 4;
						j = rand() % 4;
					}
					while(grid[i][j]);
					
					grid[i][j] = rand() % 100;
					if (grid[i][j] < 80)
						grid[i][j] = 2;
					else
						grid[i][j] = 4;
				}
			}
			while (score != -1);
		}
		else if (choice == 2)
		{
			system("cls");
			menuArt();
			
			// display game instructions
			printf("2048 Instructions");
			printf("\n1. Open 2048.exe");
			printf("\n2. Choose Menu Option (input number 1/2/3 to proceed)");
			printf("\n	a) Play Option");
			printf("\n		- Type the word \"Start Game\" (including spaces)");
			printf("\n		- Combine the same number in the grid to create a new number by moving both numbers together");
			printf("\n		- To move a number, input character W, A, S, D then click 'Enter'");
			printf("\n		- Player wins when a number in the grid reach 2048");
			printf("\n		- The game is over when no number can be moved or combined");
			printf("\n	b) Instruction Option");
			printf("\n		Shows game instructions");
			printf("\n	c) Exit Option");
			printf("\n		Exit the program");
			printf("\n\nPress 'Enter' to continue");
			
			getchar();
			system("cls");
		}
	}
	while (choice != 3);
	
	// display exit message
	puts("");
	printf("Thank you for playing (^-^)/\n");
	printf("Made by: jowenzero\n");
	getchar();
	
	return 0;
}

// 2048 game art display function
void menuArt()
{
	printf("\n");
	printf("=====   =====   =   =   =====\n");
	printf("    |   |   |   |   |   |   |\n");
	printf("|===|   |   |   |===|   |===|\n");
	printf("|       |   |       |   |   |\n");
	printf("=====   =====       |   =====\n");	
	printf("=============================\n");
	printf("\n");
}

// start word validation function
bool validStart(char start[])
{
	if (strcmp(start, "Start Game") == 0)
		return true;
	else
		return false;
}

// cursor location function
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

// grid check for possible moves function
// if possible move exist, returns true
bool gridCheck(int grid[4][4])
{
	int i, j;
	
	// check if grid have empty space
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if(!grid[i][j])
				return true;
	
	// check if grid have at least one pair of same number for possible moves
	// scan from up to down and left to right
	for (i = 0; i < 4; i++)
		for (j = 0; j < 3; j++)
		{
			if (grid[i][j] && grid[i][j] == grid[i][j + 1])
			{
				return true;
			}
			else if (grid[j][i] && grid[j][i] == grid[j + 1][i])
			{
				return true;
			}
		}
	
	// check if grid have at least one pair of same number for possible moves
	// scan from down to up and right to left
	for (i = 0; i < 4; i++)
		for (j = 3; j > 0; j--)
		{
			if (grid[i][j] && grid[i][j] == grid[i][j - 1])
			{
				return true;
			}
			if (grid[j][i] && grid[j][i] == grid[j - 1][i])
			{
				return true;
			}
		}
		
	return false;
}

// grid duplicate check function
// check if current grid is identical to saved grid to determine if any number has moved
// returns true if any number has moved
bool duplicateCheck(int array[4][4], int array2[4][4])
{
	int i, j;
	
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			if (array[i][j] != array2[i][j])
				return true;
	
	return false;
}
