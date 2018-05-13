#include "allcode_api.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main()
{
	FA_RobotInit();
	FA_LCDBacklight(100);
	
	while(1)
    {
		FA_SetMotors(100,84);
		FA_Right(88);
		FA_DelaySecs(2);
	}
	return 0;
}