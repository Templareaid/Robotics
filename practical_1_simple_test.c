/* Simple skeletontest program for in-robot API */

#include "allcode_api.h"
#include "allcode_lib.h"

   
int main()
{
	FA_RobotInit();
    
    FA_LCDBacklight(50);

	// 1 unit = 0.32mm
	// 10cm = 31.25 unit
    while(1)
    {   
	FA_SetMotors(50, 47);
	
		//Smaller ir means more distance
        if(FA_ReadIR(1) > 150)  // check front left ir
        {	
			FA_Backwards(50);
            FA_Right(45);      
        }

        if(FA_ReadIR(2) > 150)  // check front ir, spin 180
        {
			FA_Backwards(60);
			FA_Right(180);
        }

        if(FA_ReadIR(3) > 150)  // check front right ir
        {
			FA_Backwards(50);
            FA_Left(45);      
        }

        

        FA_LCDPrint("Hello", 5, 20,25,FONT_NORMAL, LCD_OPAQUE);

        FA_LCDClear();
        FA_LCDNumber(FA_ReadEncoder(CHANNEL_LEFT), 0, 0, FONT_NORMAL, LCD_OPAQUE);
        FA_LCDNumber(FA_ReadEncoder(CHANNEL_RIGHT), 40, 0, FONT_NORMAL, LCD_OPAQUE);
    
        FA_LCDNumber(FA_ReadBattery, 0, 8, FONT_NORMAL, LCD_OPAQUE);
     
        FA_LCDNumber(FA_ReadLine(CHANNEL_LEFT), 0, 16, FONT_NORMAL, LCD_OPAQUE);
        FA_LCDNumber(FA_ReadLine(CHANNEL_RIGHT), 80, 16, FONT_NORMAL, LCD_OPAQUE);
        
        if(FA_ReadSwitch(0) == 1)
            FA_PlayNote(1200,200);
        if(FA_ReadSwitch(1) == 1)
            FA_PlayNote(2200,200);
        
		FA_DelayMillis(100);
        
        int i;
        for (i = 0; i < 8; i++) {
            if (FA_ReadIR(i) > 600) {
                FA_LEDOn(i);
            }
            else {
                FA_LEDOff(i);
            }
        }
    }            
 	return 0;
}

/*	F shape
        // Go forward
        FA_SetMotors(50, 47);
		FA_Forwards(312);
		FA_Right(90);
		int j;
		for(j = 0; j < 2; j++)
		{
			FA_Forwards(125);
			FA_Backwards(125);
			FA_Right(90);
			FA_Forwards(104);
			FA_Left(90);
		} 
		FA_Left(90);
*/

/*	E shape
		FA_SetMotors(50, 47);
		FA_Forwards(312);
		FA_Right(90);
		int j;
		for(j = 0; j < 2; j++)
		{
			FA_Forwards(125);
			FA_Backwards(125);
			FA_Right(90);
			FA_Forwards(104);
			FA_Left(90);
		} 
		FA_Forwards(125);
		FA_Backwards(125);
		FA_Left(90);
		FA_Right(1080);
*/	