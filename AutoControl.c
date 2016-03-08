#include "includes.h" 

/*-----------------------------------------------
函数：   AutoControl  
目的：   PID 算法控制方向和速度
输入：   期望的方向和两个舵机的期望速度 实际速度 
输出：   舵机方向输出  两个舵机速度输出 
            
错误：   PWM级联不能采用单独访问的方法   


------------------------------------------------*/






  static int16 duty; 

   
    
    
void  Motor_PID(void) {
   
      static int16   erro0_left=0,erro1_left=0,erro2_left=0;
      static int16   erro0_right=0,erro1_right=0,erro2_right=0;
      
      
      static int16   duty_left=100,duty_right=100;
      uint8 beta1,beta0;
      int ii;
      
       
    ///////刹车判断///////////////
    //////////////////////////////
   
  //       Sci_write(CurrentSpeed_left);
  //       Sci_write(0xff);
  //        Sci_write(CurrentSpeed_right);
         
         
   
  ///////////////减速处理程序/////////////////////////////////////////////////////   
                                                                                //
    if(((CurrentSpeed_left+CurrentSpeed_right)>>1-ExpectSpeed)>0) {             //
                                                                                //
                                                                                //
            Motor_left=0;                                                       //
            Motor_right=0;                                                      //
                                                                                //
                                                                                //
                                                                                //
            Motor_left=0;                                                       //
            Motor_right=0;                                                      //
                                                                                //
             Motor_left_r=100;                                                  //
             Motor_right_r=100;                                                 //
                                                                                //
           for(ii=0;ii<30000;ii++);                                             //
           for(ii=0;ii<30000;ii++);
           for(ii=0;ii<30000;ii++); 
           for(ii=0;ii<30000;ii++);
           for(ii=0;ii<30000;ii++);                                             //
                                                                                //
               Motor_left_r=0;                                                  //
               Motor_right_r=0;                                                 //
                                                                                //
  /*  if(((CurrentSpeed_left+CurrentSpeed_right)>>1-ExpectSpeed)>6) {           //
               Motor_left_r=100;                                                //
               Motor_right_r=100;                                               //
                                                                                //
           for(ii=0;ii<30000;ii++);                                             //
            for(ii=0;ii<30000;ii++);                                            //
                                                                                //
               Motor_left_r=0;                                                  //
               Motor_right_r=0;                                                 //
                                                                                //
                                                                                //
                                                                                //
              }                                                                 //
    */                                                                          //
                                                                                //
      }                                                                         //
     /////////////////////////////////////////////////////////////////////////////
     
     
     
     //////最小速度限制//////// 
      
      
      if(ExpectSpeed<20)
          ExpectSpeed=20;
      /////////////////// 
 
     
 
   
       //差速控制  计算 
    
       //////////////////////////////
         
        //ExpectSpeed=25;
       /////////////////////////////
   
  
     if(ExpectDirection>0) {
        
         ExpectSpeed_left = ExpectSpeed ;
         ExpectSpeed_right= ExpectSpeed+abs(ExpectSpeed*abs(duty)/350); 
       
     
     }
      
      else {
      
           ExpectSpeed_right=ExpectSpeed;
           ExpectSpeed_left =ExpectSpeed+abs(ExpectSpeed*abs(duty)/350);
     
      }
    
      
  /*       
       
        ExpectSpeed_left= 0x60;
        ExpectSpeed_right=0x60;
       
   */   
   
       
       
       
       
   ///  if( !(ExpectSpeed_right%16))
  ///               ExpectSpeed_right--;
          
     
       erro0_left = ExpectSpeed_left - CurrentSpeed_left;
       erro0_right= ExpectSpeed_right- CurrentSpeed_right;
      
/////////////////////////////////////       判断是否超调  
///     Y： 采用pd控制
///     N： 采用pid 控制  
//////////////////////////////////////      
 
      
      duty_left+=(erro0_left-erro1_left)*Kp_left     + erro0_left *Ki_left +
                 (erro0_left+erro2_left-erro1_left<<1)*Kd_left;
                 
                        
      duty_right+=(erro0_right-erro1_right)*Kp_right + erro0_right*Ki_right+
                  (erro0_right+erro2_right-erro1_right<<1)*Kd_right;  
      
      
      
     erro2_left=erro1_left;
     erro1_left=erro0_left;
     
     erro2_right=erro1_right;
     erro1_right=erro0_right;
     
  ///////////////////////////////////////  
    
 //    duty_left= ExpectSpeed;
 //    duty_right=ExpectSpeed; 
    
 ////////////////////////////////////////    
 
 
 
     
     
      if(duty_right>100) {
        
            duty_right=100;
        
      }
      
      if (duty_right<0) {
      
            duty_right=0;
    
      
      }
     
  
  
  
  
     
      if(duty_left>100){
         duty_left=100;                         //防止超调 ，设定最小值  
 
                         
        }
       if(duty_left<0) {
           duty_left=0;
        
      }
    
    
    
    
    
    
    
    
    
    
    
    
    if(!stoped){
      
     
      Motor_left=duty_left;
      Motor_right=duty_right;
      
      
    }
    
       
}


void Steer_PID(void) {

      static int16 erro0,erro1,erro_sum;
      
      static int16 last_direction=0;
      
      int direct=0;
      
 
   /*   
     erro0=ExpectDirection-last_direction;
     erro_sum+=erro0; 
        
      duty=erro0*Steer_Kp+(erro0-erro1)*Steer_Kd+erro_sum*Steer_Ki;  
     
        
      if(duty<-220) {
        duty=-220;
       erro_sum-=erro0;
      }
      else if (duty>220) {
        duty=220;
        
        erro_sum-=erro0;
      }
        erro1=erro0;
     
     
      last_direction=duty;
     
    */
    
    
  
  
  /*修改后，不采用pid算法*/     
    
    if(ExpectDirection<-220)
         duty=-220;
    
   else  if(ExpectDirection>220)
         duty=220;
    
   else duty=ExpectDirection;
   
    
    /////////////////////////
     
     
     
      direct=Direction_mid+duty;
      
      
     
      
      
      SteerDirection=direct;

}                      

 void AutoControl(void)

{
    
    
    
     
   
    Steer_PID();
    
    
    Motor_PID();
      
      
  
      
}






























  
