#include "allcode_api.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
   
int main()
{
	FA_RobotInit();
	
	FA_SetMotors(0,0);
	
	FA_LCDBacklight(100);
	FA_LCDClear();

	// 1 unit = 0.32mm
	// 10cm = 31.25 unit
	
	int j = 0;
    while(1)
    {   	
		FA_LCDClear();	
		FA_LCDNumber(FA_ReadIR (0), 0, 0, FONT_NORMAL, LCD_OPAQUE);
		
		
		FA_LCDNumber(FA_ReadIR (1), 30, 0, FONT_NORMAL, LCD_OPAQUE);
		
		
		FA_LCDNumber(FA_ReadIR (2), 60, 0, FONT_NORMAL, LCD_OPAQUE);
		
		
		FA_LCDNumber(FA_ReadIR (3), 90, 0, FONT_NORMAL, LCD_OPAQUE);
		
		
		FA_LCDNumber(FA_ReadIR (4), 0, 10, FONT_NORMAL, LCD_OPAQUE);
		
		
		FA_LCDNumber(FA_ReadIR (5), 30, 10, FONT_NORMAL, LCD_OPAQUE);
		
		
		FA_LCDNumber(FA_ReadIR (6), 60, 10, FONT_NORMAL, LCD_OPAQUE);
		
		
		FA_LCDNumber(FA_ReadIR (7), 90, 10, FONT_NORMAL, LCD_OPAQUE);
		
		
		FA_DelayMillis(100);
		
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