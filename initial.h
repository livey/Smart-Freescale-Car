#ifndef INITIAL_H
#define INITAIL_H

#include "types.h"  

#define Motor_right      PWMDTY3 
#define Motor_left       PWMDTY4 
#define SteerDirection   PWMDTY01 
#define Motor_right_r    PWMDTY2 
#define Motor_left_r     PWMDTY5 

void  System_init(void);
void  Sci_write(uint8);
uint8 Sci_read(void);

 




#endif 