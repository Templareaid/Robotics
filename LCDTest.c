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
		FA_LCDBPlot(10, 10);
	}
	return 0;
}