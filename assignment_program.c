#include "allcode_api.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int state = 1;
// 1 = North
// 2 = East
// 3 = South
// 4 = West
	
// Coordinates start at 3 so they can never go below 0 no matter the starting position or orientation
int mapXstart = 3;
int mapYstart = 3;
int mapXcurrent = 3;
int mapYcurrent = 3;

// Positions for drawing the maze on the LCD
int startX = 0;
int startY = 0;
int endX = 40;
int endY = 15;

// Positions the robot on the LCD
int robotX;
int robotY;

// When above 0, the nest has been found
int nest;

// Keeps track of which direction the robot is facing
void BTState()
{
	FA_BTSendString("(",2);
	FA_BTSendNumber(mapXcurrent);
	FA_BTSendString(",",2);
	FA_BTSendNumber(mapYcurrent);
	FA_BTSendString(")",2);
	FA_BTSendString(" - ",4);
	
	if (state == 1)
	{
		FA_BTSendString(" North\n", 8);
	}
	
	if (state == 2)
	{
		FA_BTSendString(" East\n", 8);
	}
	
	if (state == 3)
	{
		FA_BTSendString(" South\n", 8);
	}
	
	if (state == 4)
	{
		FA_BTSendString(" West\n", 8);
	}
}

// Makes the robot avoid obstacles
void avoidwalls()
{
	// Avoid front wall
	if (FA_ReadIR (2) > 1200)
	{
		FA_Backwards(10);
	}

	// Avoid back wall
	if (FA_ReadIR (6) > 625)
	{
		FA_Forwards(10);
	}
	
	// Avoid back right wall
	if (FA_ReadIR (5) > 450)
	{
		FA_Left(11);
		FA_Forwards(10);
	}
	
	// Avoid back left wall
	if (FA_ReadIR (7) > 450)
	{
		FA_Right(10);
		FA_Forwards(10);
	}

	// Avoid left wall
	if (FA_ReadIR (1) > 265)
	{	
		FA_Backwards(5);
		FA_Right(7);
	}
		
	// Avoid right wall
	if (FA_ReadIR (3) > 185)
	{
		FA_Backwards(5);
		FA_Left(8);
	}
	
	// Emergency left turn
	if (FA_ReadIR (3) > 250 && FA_ReadIR (7) > 450)
	{
		FA_Backwards(10);
		FA_Left(32);
	}

	// Emergency right turn
	if (FA_ReadIR (1) > 350 && FA_ReadIR (5) > 450)
	{
		FA_Backwards(10);
		FA_Right(30);
	}	
}

// Determines if the robot has to turn left, go straight on or turn right
void followWalls()
{
	// Turns left and sets correct orientation
	if (FA_ReadIR (0) < 50)
	{
		FA_Left(93);
		FA_DelayMillis(45);
		
		if (state == 1)
		{
			state = 4;
		}
		
		else if (state == 4)
		{
			state = 3;
		}
		
		else if (state == 3)
		{
			state = 2;
		}
		
		else if (state == 2)
		{
			state = 1;
		}
	}
	
	// Go forwards
	else if (FA_ReadIR (2) < 50)
	{
		FA_SetMotors(100,84);
	}
	
	// Turns right and sets correct orientation
	else if (FA_ReadIR (4) < 50)
	{
		FA_Right(91);
		FA_DelayMillis(45);
		
		if (state == 1)
		{
			state = 2;
		}
		
		else if (state == 2)
		{
			state = 3;
		}
		
		else if (state == 3)
		{
			state = 4;
		}
		
		else if (state == 4)
		{
			state = 1;
		}
	}
	
	// About turn when in a dead end
	else
	{
		FA_Right(184);
		FA_DelayMillis(45);
		
		if (state == 1)
		{
			state = 3;
		}
		
		else if (state == 2)
		{
			state = 4;
		}
		
		else if (state == 3)
		{
			state = 1;
		}
		
		else if (state == 4)
		{
			state = 2;
		}
	}
	avoidwalls();
}

// Draws the maze to the LCD
void drawMaze()
{
	// Updates map if traveling North
	if (state == 1)
	{
		startX = endX;
		startY = endY;
		endY = endY - 3;
		mapYcurrent = mapYcurrent + 1;
		
		robotX = endX;
		robotY = endY + 2;
	}
		
	// Updates map if traveling East
	if (state == 2)
	{
		startX = endX;
		startY = endY;
		endX = endX + 3;
		mapXcurrent = mapXcurrent + 1;
		
		robotX = endX - 2;
		robotY = endY;
	}
	
	// Updates map if traveling South
	if (state == 3)
	{
		startY = endY;
		startX = endX;
		endY = endY + 3; 
		mapYcurrent = mapYcurrent - 1;
		
		robotX = endX;
		robotY = endY - 2;
	}
	
	// Updates map if traveling West
	if (state == 4)
	{
		startX = endX;
		startY = endY;
		endX = endX - 3;
		mapXcurrent = mapXcurrent - 1;
		
		robotX = endX + 2;
		robotY = endY;
	}
	
	// Draws map
	FA_LCDLine(startX,startY,endX,endY);
	
	// Can be used to track robots positions
	// Need to fill in gaps where robot was
	FA_LCDBPlot(robotX,robotY);
	
	FA_DelayMillis(220);
	FA_SetMotors(0,0);
	FA_DelayMillis(30);
}

// Turns all LED's on
void allLEDOn()
{
	FA_LEDOn(0);
	FA_LEDOn(1);
	FA_LEDOn(2);
	FA_LEDOn(3);
	FA_LEDOn(4);
	FA_LEDOn(5);
	FA_LEDOn(6);
	FA_LEDOn(7);
}

// Turns all LED's off
void allLEDOff()
{
	FA_LEDOff(0);
	FA_LEDOff(1);
	FA_LEDOff(2);
	FA_LEDOff(3);
	FA_LEDOff(4);
	FA_LEDOff(5);
	FA_LEDOff(6);
	FA_LEDOff(7);
}

// Victory dance once nest has been found a second time
void victory()
{
	// If the light sensor goes below 700, it is under the nest
	if (FA_ReadLight() < 700)
	{
		FA_SetMotors(100,84);
		FA_Right(920);
		FA_BTSendString("Maze completed\n",16);
		FA_BTSendString("La Victoire!\n",14);
		
		int random;
		
		// Turn LED's on in random order
		int LEDTurnOn;
		for (LEDTurnOn = 0; LEDTurnOn < 7; LEDTurnOn++)
		{
			random = rand()%7;
			FA_LEDOn(random);
			FA_DelayMillis(100);
		}
		
		// Turn LED's off in random order
		int LEDTurnOff;
		for (LEDTurnOff = 0; LEDTurnOff < 7; LEDTurnOff++)
		{
			random = rand()%7;
			FA_LEDOff(random);
			FA_DelayMillis(100);
		}
		
		// Play random tune
		int playTune;
		for (playTune = 0; playTune < 5; playTune++)
		{
			random = rand()%10;
			
			FA_PlayNote ((random * 100), 250);
			
			FA_DelayMillis (100);
		}
		FA_DelaySecs(5);
	}
}

// Detects when the nest has been found
void foundNest()
{
	// Detects nest
	if (FA_ReadLight() < 400)
	{
		// If nest has been found more than once, victory
		if (nest > 0)
		{
			victory();
		}
		FA_BTSendString("Found nest\n",12);
		allLEDOn();
		FA_Right(184);
		FA_PlayNote (250, 100);
		allLEDOff();
		
		// Update state once turning in the nest
		if (state == 1)
		{
			state = 3;
		}
		
		else if (state == 2)
		{
			state = 4;
		}
		
		else if (state == 3)
		{
			state = 1;
		}
		
		else if (state == 4)
		{
			state = 2;
		}
		
		// Move out of nest and update coordinates
		FA_Forwards(100);
		if (state == 1)
		{
			startX = endX;
			startY = endY;
			endY = endY - 4;
			mapYcurrent = mapYcurrent - 1;
			
			robotX = endX;
			robotY = endY + 2;
		}
			
		// Updates map if traveling East
		if (state == 2)
		{
			startX = endX;
			startY = endY;
			endX = endX + 4;
			mapXcurrent = mapXcurrent + 1;
			
			robotX = endX - 2;
			robotY = endY;
		}
		
		// Updates map if traveling South
		if (state == 3)
		{
			startY = endY;
			startX = endX;
			endY = endY + 4; 
			mapYcurrent = mapYcurrent + 1;
			
			robotX = endX;
			robotY = endY - 2;
		}
		
		// Updates map if traveling West
		if (state == 4)
		{
			startX = endX;
			startY = endY;
			endX = endX - 4;
			mapXcurrent = mapXcurrent - 1;
			
			robotX = endX + 2;
			robotY = endY;
		}
		FA_LCDLine(startX,startY,endX,endY);
		BTState();
		nest++;
	}
}

int main()
{
	FA_RobotInit();
	srand((unsigned)time(0));
	FA_LCDBacklight(100);
	FA_LCDSetForeground (0);
	FA_LCDSetBackground (1);
	FA_LCDClear();

	// Let user know robot is connected via blue-tooth
	FA_BTSendString("Orbit Connected\n", 20);
	
	// Wait, then adjust and begin
	FA_DelaySecs(2);
	followWalls();
	FA_LCDClear();
	
	while(1)
    {
		// Full steam ahead
		FA_SetMotors(100,84);
		/* 
		*  When the sensors read a line, draw the next step of the maze, delay until the robot is in
		*  the center of the square and set the motors to 0 so it stops, delay slightly again,
		*  output the state to bluetooth, check to see if the robot is in the nest
		*  then detect any nearby walls and turn according. If the nest has been found once
		*  and the current coordinates are the same as the starting ones
		*  then beep to let the user know it has gone back to the start.
		*  Follow the walls again until the nest is found a second time and then do the victory dance
		*/
		if (FA_ReadLine (0) < 200 && FA_ReadLine (1) < 300)
		{	
			FA_LCDPlot(robotX,robotY);
			drawMaze();
			BTState();
			foundNest();
			followWalls();
			if (nest > 0 && mapXcurrent == mapXstart && mapYcurrent == mapYstart)
			{
				FA_PlayNote (500, 250);
				FA_BTSendString("Back to starting point\n",25);
			}
		}
	// After every movement into a square, reorientates away from walls for neater movement
	avoidwalls();
	}
	return 0;
}

/*
	int xCoord = 4;
	int yCoord = 4;
	// Keeps track to make sure every square has been visited
	int mapCoords[xCoord][yCoord] =
	{
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,1,0,0},
	};
	
	
	for (xCoord = 0; xCoord < 4; xCoord++)
		{
			for (yCoord = 0; yCoord < 4; yCoord++)
			{
				if (xCoord > 0)
				{
					FA_BTSendNumber(xCoord);
				}
				
				if (yCoord > 0)
				{
					FA_BTSendNumber(yCoord);
				}
			}
		}
		
	Breadcrumb method:
	Leave breadcrumbs incrementing by 1 with each square passed once the nest has been found
	Once all 16 squares are found, follow the breadcrumbs back always following the lowest
	number available to the current occupied square
	
	int breadCrumbs[4][4] =
	{
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
	};
	*/