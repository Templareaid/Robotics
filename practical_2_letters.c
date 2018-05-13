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
		if (FA_ReadSwitch(0) == 1)
		{
			//E shape
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
		}
		
		if (FA_ReadSwitch(1) == 1)
		{
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
		}
        
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