/******************************************************************************************

MIT License

Copyright (c) 2017 Brett Holman

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************/
 
#include <MKL25Z4.H>
#include <stdlib.h>

#include <string.h>
#include "util.h"
#include "gpio_defs_main.h"

#define TIME 50
using namespace std;

//initializing the COL and column LED matrix for the "game-over" message
const char gameOverScreen[COL][ROW] = {
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
{0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0},
{0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,0,0},
{0,1,1,0,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,0,1,0,1,1,0,0,1,1,1,1,0,0},
{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,0,0},
{0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,1,1,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0},
{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0},
{0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0},
{0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0},
{0,0,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,0,0,1,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
};

const char tetrisScreen[COL][ROW] = {
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
};
const char winScreen[COL][ROW] = {
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
{0,1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,0,0,1,1,0,0},
{0,1,0,1,0,1,0,0,1,0,0,1,1,0,1,0,0,1,1,0,1,0,0,1,0,0,0,0,1,0,1,0},
{0,1,0,1,0,1,0,0,1,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,1,1,0,0},
{0,1,0,1,0,1,0,0,1,0,0,1,0,1,1,0,0,1,0,1,1,0,0,1,0,0,0,0,1,0,1,0},
{0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,0,0,1,0,1,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
};

char screen[ROW][COL]; // TODO: Fix this. This will cause confusion.  Row and column are rotated from the direction of the other matrices.

/*----------------------------------------------------------------------------
 MAIN function
*----------------------------------------------------------------------------*/
int main (void) {
	
	
	int startSpeed(TIME), gameSpeed(TIME);//350;
	int test_var(0), type, difficulty=1;
	int i, j, rowsDone(1);
	const bool TESTING = false;
	
	if (TESTING) 
		test_var = -1;
	else 
		test_var = 3;
	
	// Shape Initialization
	Line newLine(5,MAXY+2,2);		
	Square newSquare(6,MAXY+2,3);
	T newT(7,MAXY+3,4);
  //Z1 newZ1(8,MAXY+test_var,5); // TODO: fix this object
	Shape *current;
	
	//Testing setup
	if(!TESTING) current = &newSquare;//&newLine;
	else 
		current = &newT;//Z1;
	
	// Set the scene
	init();
	initLED();
	for(i = 0; i < ROW; i++){
		for(j = 0; j < COL; j++){
			screen[i][j] = tetrisScreen[j][i];
		}
	}
	
	// The game starts here
	while((*current).isFalling())
	{
		pause(gameSpeed, (*current));
		
		(*current).move_d();
		
		// Stops falling
		if(!(*current).isFalling()) 
		{
			if(!TESTING)
			{
				// Generate new block				
				type = (*current).getType();
				if(type==0)
					current=&newLine;
				else if(type == 1)
					current=&newT;
				else if(type == 2)
					current=&newSquare;//&newZ1;
				else if(type == 3)
					current=&newSquare;
			}
			(*current).make(5,MAXY);
			pause(gameSpeed, (*current));
			
			//Shift stack down and removes completed rows
			for(int k=MINY;k<MAXY;k++)
			{					
				// Break at top of stack
				if(isRowEmpty(k))
					break;
				
				// Remove Completed Rows
				if(isRowComplete(k))
				{ 
					clearRow(k);
					
					// Increase difficulty
					gameSpeed = startSpeed*difficulty_curve(difficulty);
					difficulty++;
					
					// Increment Score (green counter on left)
					screen[rowsDone++][0]=3;	// TODO: write a function to do this
					pause(gameSpeed, (*current));
					
					// Shift row down
					for(int l=k+1;l<MAXY;l++)
					{
						if(isRowEmpty(l))
							break;
						shiftRowDown(l);
					}
					// This decrements so that you start over checking 
					// at the newley completed row 
					k--;
				}
			}
		}
	}
	
	// End of game
	gameOver();
}

