#include "includes.h"

 
 

 
 
 
 
 /*--------------------------------------------------
  函数： long_delay()
  目的： 为传送数据提供一个短暂的延时，避免丢失数据
  输入： 无 
  输出： 无
  错误： 无
  -------------------------------------------------*/ 

void long_delay(void) {
    uint16 k,l;
     
     
       for(k=0;k<2;k++)
       for(l=0;l<500;l++);
}


 /*--------------------------------------------------
  函数：  print_init_map
  目的：  打印采集的原始图像 
  输入：  无 
  输出：  用串口 输出到上位机
  错误：  map_point 指针没有初始化 
  -------------------------------------------------*/ 



void print_init_map(void){

  uint16 ii;
  uint8 *map_point=&ImageBuffer[0][0];
 

 for(ii=0;ii<RealRow*RealColumn;ii++) 
 {
  
        Sci_write(*map_point);
        map_point++;   
 }

 
}



 



void print_centerline(void) {

uint16 ii;
uint8 *point=&CenterLine[0];

for(ii=0;ii<RealRow;ii++) {
       
       
       Sci_write(*point);
       point++;
   
    }
    
    
}  

 
void print_binarymap(void) {

    uint16 jj;
    uint8 *point=&ImageBuffer[0][0];
   
   
   
    for(jj=0;jj<RealRow*RealColumn;jj++) {
         
         if(*point==1)
             Sci_write('1');
         else Sci_write('0');
         point++;
         
         if(!(jj%RealColumn) && jj!=0)
         Sci_write(10);
         
        }
    }
            

  void SystemStop(void){
  
       Motor_left=0;
       Motor_right=0;
       SteerDirection=Direction_mid;
       while(1);
  
  
  }
  
  
 void VoidBreak(void) 
 {
 
   if(CurrentSpeed_left<=10 && CurrentSpeed_right<=10)
   
     SystemStop();
 
 
 }
  
  
  
  
  
  
  
  
 