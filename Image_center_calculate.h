#ifndef  IMAGE_CENTER_CALCULATE
#define  IMAGE_CENTER_CALCULATE
#include "types.h"
 
  
extern uint8 CenterLine[RealRow];   //传递 此参数供后面过程计算使用  并且尽快完成，
extern uint8 DeadLine;                                    //提高 cpu 利用率 
extern uint8 StartLine; 
void ImageCenterCalculate(void);

   
#endif    
   