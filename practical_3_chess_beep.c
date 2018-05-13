/* Simple skeletontest program for in-robot API */

#include "allcode_api.h"
#include "allcode_lib.h"
   
int main()
{
	FA_RobotInit();
    
	FA_LCDBacklight(50);
	FA_LCDClear();
	FA_LCDPrint("'Hello,", 10, 40,0,FONT_NORMAL, LCD_OPAQUE);
	FA_LCDPrint("my name", 10, 40,10,FONT_NORMAL, LCD_OPAQUE);
	FA_LCDPrint("is Orbit'", 10, 40,20,FONT_NORMAL, LCD_OPAQUE);

	// 1 unit = 0.32mm
	// 10cm = 31.25 unit
	
	int j = 1;
    while(1)
    {   
		//Smaller ir means more distance
        if(FA_ReadIR(1) > 150)  // check front left ir
        {	
			//FA_LCDClear();
        }

        if(FA_ReadIR(2) > 150)  // check front ir, spin 180
        {
			//FA_LCDClear();
        }

        if(FA_ReadIR(3) > 150)  // check front right ir
        {
			//FA_LCDClear();
        }
		
        //FA_LCDClear();
        //FA_LCDNumber(FA_ReadEncoder(CHANNEL_LEFT), 0, 0, FONT_NORMAL, LCD_OPAQUE);
        //FA_LCDNumber(FA_ReadEncoder(CHANNEL_RIGHT), 40, 0, FONT_NORMAL, LCD_OPAQUE);
    
        //FA_LCDNumber(FA_ReadBattery, 0, 8, FONT_NORMAL, LCD_OPAQUE);
     
        //FA_LCDNumber(FA_ReadLine(CHANNEL_LEFT), 0, 16, FONT_NORMAL, LCD_OPAQUE);
        //FA_LCDNumber(FA_ReadLine(CHANNEL_RIGHT), 80, 16, FONT_NORMAL, LCD_OPAQUE);
				
			
			if (FA_ReadSwitch(0) == 1)
			{	
				if(j==1)
				{
					FA_LCDClear();
					FA_LCDPrint("'What are", 10, 40,0,FONT_NORMAL, LCD_OPAQUE);
					FA_LCDPrint("we doing", 10, 40,10,FONT_NORMAL, LCD_OPAQUE);
					FA_LCDPrint("Today?'", 10, 40,20,FONT_NORMAL, LCD_OPAQUE);
				}

				if(j==2)
				{
					FA_LCDClear();
					FA_LCDPrint("'How about", 12, 35,0,FONT_NORMAL, LCD_OPAQUE);
					FA_LCDPrint("a nice game", 12, 35,10,FONT_NORMAL, LCD_OPAQUE);
					FA_LCDPrint("of Chess?'", 10, 35,20,FONT_NORMAL, LCD_OPAQUE);
				}
				j++;
			}

		if(FA_ReadSwitch(1) == 1)
		{
			FA_PlayNote (1000, 100);
			FA_PlayNote (1500, 100);
			FA_PlayNote (2000, 100);
			FA_PlayNote (2500, 100);
			FA_PlayNote (3000, 100);
			
			FA_DelayMillis (750);
			
			FA_PlayNote (3000, 100);
			FA_PlayNote (2500, 100);
			FA_PlayNote (2000, 100);
			FA_PlayNote (1500, 100);
			FA_PlayNote (1000, 100);
		}

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
/*
if(FA_ReadSwitch(0) == 1)
		{
			FA_LCDClear();
			FA_LCDRectangle (0, 0, 127, 31, LCD_OPAQUE, 0);
		}

		if(FA_ReadSwitch(1) == 1)
		{
			FA_LCDClear();
			FA_LCDRectangle (10, 10, 117, 21, LCD_OPAQUE, 0);
		}
*/