#ifndef INTERRUPTS_H
#define INTERRUPTS_H

#include "types.h" 

#define RealRow      (60)    //实际需要的采样行数和列数  
#define RealColumn   (110)

#define Line_max     (240)   //最大中断行数为 240行/帧 
#define Line_min     (0)  

#define Row_max      (60)    //设置的实际最大采样行数  
#define Row_min      (0) 

#define Column_min   (0) 
#define Column_max   (110)    //设置的最大采样列数 

#define Mid_line      52   
 
extern uint8 SampleLock;     // 两把锁： 图像采集锁和图像处理锁  
extern uint8 ProcessLock; 
extern uint8 ImageBuffer[RealRow][RealColumn];    //存储图像数据  

extern int16 CurrentSpeed_left;    // 当前速度值    
extern int16 CurrentSpeed_right;  

extern uint16 system_time;

#endif  