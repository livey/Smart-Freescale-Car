#include "includes.h" 

#define Adot 15 
#define Bdot 40          ///40

#define SafeSpeed  20
#define BreakSpeed 10
#define SpeedMax   80        //80

#define A0 13
#define A1 7    //低于这个速度则按照最小速度原则 
 
 
#define Direct_P  310
 

//   #define maxspeed  110
 //  #define minspeed  20
#define minline   10
#define maxline   59     

 

/*----------------------------------------------------
函数ImageProcess 
目的：对提取中心线后的图像进行处理 得到预计方向和速度
输入：二值化后的图像
输出：期望的方向输出    期望的两个电机输出  
错误：
-----------------------------------------------------*/  


 int16  ExpectDirection;
 uint16 ExpectSpeed_left;
 uint16 ExpectSpeed_right;
 uint16 ExpectSpeed;
 int16 speed;
 
 uint8 MAX_SPEED;
 uint8 MIN_SPEED;
 

/*提取 期望的速度与方向*/

 
 
 


void ImageProcess(void)  {
  
   
      int offset;
      int ii,sum_all,sum_back;
		  int R;
		  int Speed;

		  int  k1,k2,k3;
		  int a0,a1,a2,a3;
		  long  jj;
		  long  aa,bb;
		  
		  
		  int16 zuobiao[RealRow]={0};


   ///////////////////////////////////////////
            ///////坐标变换/////////
    /////////////变换成实际的坐标/////////////
    

       for(ii=0;ii<RealRow;ii++)
           zuobiao[ii]=(CenterLine[ii]-Mid_line)*ii/50+(CenterLine[ii]-Mid_line)>>1;
           




     /*利用图像分割原理*/

 
	 /*图像参考线动态调整*/  //速度控制  

   if(DeadLine==0)
   
     {
        ExpectDirection=ExpectDirection/abs(ExpectDirection)*220;
        ExpectSpeed=SafeSpeed;
   
        return;  
     }
   
    else  if( DeadLine<7)
		  {
			  

			  ExpectDirection=(zuobiao[DeadLine]/abs(zuobiao[DeadLine]))*220;
			  ExpectSpeed=SafeSpeed;

			  return;                                

          }
	 else if(DeadLine<Adot)
		   {


			 a1=zuobiao[DeadLine]+zuobiao[DeadLine-1]+zuobiao[ii-2]+zuobiao[ii-3];
			 a1>>=2;
        

			   ExpectDirection=Direct_P*a1/DeadLine;                           // 需要校正的系数 


			   

		    }
      else if (DeadLine>=Adot)
		    {



				 ii=(DeadLine-60)*(Bdot-Adot)/(60-Adot)+Bdot;

			 
				
				a1=zuobiao[ii]+zuobiao[ii-1]+zuobiao[ii-2]+zuobiao[ii-3];
				a1>>=2;

				 
				  
         ExpectDirection=Direct_P*a1/ii;
  
			  }


  
 
 
 
 
 
 // 速度控制 
 
  if(DeadLine<minline)
      ExpectSpeed=MIN_SPEED;
  
  else 
  
      ExpectSpeed=MAX_SPEED-(maxline-DeadLine)*(MAX_SPEED-MIN_SPEED)/(maxline-minline);

 
 
}

       
 
 
 
 
 
 
           
   
   
int16 abs(int16 x) {

 if(x<0)
   return(-x);
   
  else return(x);


}
 
 
  
   
   