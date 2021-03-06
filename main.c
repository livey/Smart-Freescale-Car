#include "includes.h"
 


/*---------------------------------------------------------------------
  函数： 主函数
  目的： 整个函数的程序流：  
         
         图像后台采集-》图像中心线提取-》图像方向计算-� PID 速度方向输出
         
  输入：  无 
  输出：  无
  错误：  图像处理完了应该打开采样锁 ，不然主函数返回接着处理  
  
   
  ---------------------------------------------------------------------*/ 

 
 


void main(void) {

 stoped=0;
 

 DisableInterrupts;              /****系统初始化***/  

 System_init();


 SampleLock=1; 
 ProcessLock=0;
 
 EnableInterrupts;
 
 
 
   
 SteerDirection=Direction_mid;









 
 
 
 while(system_time<120);         //先停止两秒  
  
 Motor_left=100;
 Motor_right=100;                      
   
   
ThreshHold=0x80;    //0x80
  
  
  
while(1) {
  
if(!SampleLock) {               //如果没有在采样 则开始处理图像  
        
  
     ProcessLock=1; 
       
      
    
    
        
     
 //  if(Sci_read()=='a')
         
  //      print_init_map();
         
     //   print_binarymap();
       
      
     //  ThreshHold=AutoThresh(StartLine);
       
       
       ImageCenterCalculate();   //进行图像中心线提取 
   
      
       
      
     // if(Sci_read()=='a')
         
          // print_init_map();
         
      // print_binarymap();
  
    
     // while(Sci_read()!='a');       //打印图像 返回实际处理 
     
   
   
   
   if(system_time>500)          //检测起跑线  10s 之后  
      {
        
         AutoStop();
   
      }
        
    
     if(system_time>200)
       VoidBreak();
     
   
   // if(system_time>200)
   //    SystemStop();  
       
       
        ImageProcess(); 
      
        AutoControl(); 
         
         
         
  
    /*   
        Sci_write(0x00); 
        Sci_write(CurrentSpeed_right); 
        Sci_write(0xff);
        Sci_write(CurrentSpeed_left);
     
      */    
        
    
       ProcessLock=0;               //关闭处理锁  
       SampleLock=1;                //打开采样锁 
     
   
     }
    
    
   
    
     
     
      // ImageProcess();             //根据图像提取中心线后的图像 计算 角度 和 速度      
     //  AutoControl();              //根据中心线处理后得到 角度 和 期望速度值进行 PID 控制   
    
    
    
}//  end of while(1);


}