#include "allcode_api.h"
#include "allcode_lib.h"
   
int main()
{
	FA_RobotInit();
	
	FA_LCDBacklight(100);
	FA_LCDClear();
	//FA_LCDPrint("'Hello,", 10, 40,0,FONT_NORMAL, LCD_OPAQUE);
	//FA_LCDPrint("my name", 10, 40,10,FONT_NORMAL, LCD_OPAQUE);
	//FA_LCDPrint("is Orbit'", 10, 40,20,FONT_NORMAL, LCD_OPAQUE);

	// 1 unit = 0.32mm
	// 10cm = 31.25 unit
	
	int i;
    while(1)
    {   
		if(FA_ReadSwitch(0) == 1)
		{
			int i;
			for (i = 1; i < 11; i++)
			{	
				int j = i * 10;
				FA_DelaySecs(1);
				FA_LCDClear();
				FA_ResetEncoders();
				FA_SetMotors(j,j);
				FA_DelaySecs(5);
				FA_LCDNumber(FA_ReadEncoder(CHANNEL_LEFT), 0, 0, FONT_NORMAL, LCD_OPAQUE);
				FA_LCDNumber(FA_ReadEncoder(CHANNEL_RIGHT), 80, 0, FONT_NORMAL, LCD_OPAQUE);
				FA_SetMotors(0,0);
				FA_LCDPrint("Current Power = ", 20, 0, 20, FONT_NORMAL, LCD_OPAQUE);
				FA_LCDNumber(j, 100, 20, FONT_NORMAL, LCD_OPAQUE);
				FA_DelaySecs(20);
			}
		}
    }            
 	return 0;
}



/*

if (FA_ReadSwitch(0) == 1)
		{	
			if (FA_ReadEncoder (CHANNEL_LEFT) > 0 && FA_ReadEncoder (CHANNEL_RIGHT) > 0)
			{
				FA_SetMotors(0,0);
			}
			else
			{
				FA_DelayMillis(1500);
				FA_SetMotors(100,100);
				FA_DelaySecs(1);
				FA_SetMotors(0,0);
			}
		}
		
		if (FA_ReadSwitch(1) == 1)
		{
			FA_LCDClear();
			FA_ResetEncoders();
		}
		
*/