#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H
#include "types.h" 

void ImageProcess(void);

extern int16 ExpectDirection;    // 期望的方向 
extern uint16 ExpectSpeed_left;    // 期望的左轮速度
extern uint16 ExpectSpeed_right;   // 期望的右轮速度
extern uint16 ExpectSpeed;

extern uint8 MAX_SPEED;
extern uint8 MIN_SPEED; 


#endif 