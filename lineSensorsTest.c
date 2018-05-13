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
		FA_LCDClear();
		FA_LCDNumber(FA_ReadLine (0), 0, 0, FONT_NORMAL, LCD_OPAQUE);
		FA_LCDNumber(FA_ReadLine (1), 20, 0, FONT_NORMAL, LCD_OPAQUE);
		FA_DelayMillis(100);
	}
	return 0;
}