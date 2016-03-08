#include "includes.h"
uint8 SampleLock;
uint8 ProcessLock; 

uint16 system_time=0;

uint8  ImageBuffer[RealRow][RealColumn]={0}; //存储采样地图  

const uint8  SampleLine[Row_max]={                 //存储实际需要的采样行数  
                                             //通过调整此采样行数值可以调整采样密度  
/* 
4,9,14,19,24,29,34,39,44,49,
54,59,64,69,74,79,84,89,94,99,
114,119,124,129,134,139,144,149,     //前三十个点 每隔5点一个采样值   
 
152,155,158,161,164,167,170,173,176,179,
182,185,188,191,194,197,200,203,207,209,
211,213,215,216,217,219,220,222,223,225,230,233     //前三十个点每隔三个点采集一个                                     
 
*/ 

1,5,10,16,20,31,40,45,57,62,68,79,88,97,105,
112,119,126,132,137,143,   148,152,   157,161,
165,169,172,176,179,182,185,188,190,193,
195,198,200,202,204,206,208,210,213,
215,217,218,220,221,223,224,225,227,228,
229,231,233,234, 236,237 
 
                                         
};
                                                    
int16 CurrentSpeed_left =0;
int16 CurrentSpeed_right=0;  
 
uint8  TrueLine=0;                           //真实的采样行数  
uint16 LineCount=0;                          //到来了多少行 及中断了多少次数

uint16 ii,jj;


/*-------------------------------------------------------
  函数：  j口中断函数
  目的：  标志一场信号的到来 做好接受行的准备 计数器清零 
  输入：  无 
  输出：  无
  错误：   
  ------------------------------------------------------*/ 





#pragma  CODE_SEG NON_BANKED


void interrupt 24 intportj7(void){           //场中断 

     PIFJ_PIFJ7=1;                           //清中断标志
     
     system_time++;
     
     CurrentSpeed_left=PACNT;                       //每隔三十三ms进行一次速度更新 
      
      PACNT=0;                                       //清空计数器 
     
     
     CurrentSpeed_right=PORTB;
    
     PTT_PTT4=1;
     PTT_PTT4=0;                                      //清零
     PTT_PTT4=0;
     PTT_PTT4=0;
     PTT_PTT4=0;
     
     PTT_PTT4=1;
     
   //  if((CurrentSpeed_left-CurrentSpeed_right)>0xa0)   // 防止八位计数器不够用 
    //      CurrentSpeed_right<<=8;
     
     
     
                                    
     
     if(!ProcessLock) {                     //如果没有正在处理
     SampleLock=1;                          //采样上锁
     
     PIEP_PIEP7=1;                          //开启行中断
     
     LineCount=0;                           //行数计数器清零
     TrueLine=0;                            //实际采样行数清零
     
     }
 
  
 
  
 
 
 

}


/*------------------------------------------------------
  函数：  P口 中断函数  
  目的：  行中断 读取每一行的数据 组成一帧图像  
  输入：  无 
  输出：   
  错误： TureLine++ 放错了位置 导致数据采集不正确
  -----------------------------------------------------*/ 




#pragma CODE_SEG NON_BANKED                  //行中断 
 
void interrupt 56 intportp7 (void) {

        PIFP_PIFP7=1;
   
     if(LineCount==SampleLine[TrueLine]) {       //此行为需要采集的行数 
     
     
      
      
      for(ii=0;ii<RealColumn;ii++) {             //此处执行   15*RealColumn(80)   
      
         ImageBuffer[TrueLine][ii]=PORTA;        //开始采集这一行的数据 
      //  ImageBuffer[TrueLine][ii]=PORTA;
      //   ImageBuffer[TrueLine][ii]=PORTA;
        
     
      /*    取值表  建立这个表有选择的进行非等距采样       
                
           
            
           image[line][0]=PORTA;   image[line][0]=PORTA;   image[line][0]=PORTA;  
           image[line][1]=PORTA;   image[line][1]=PORTA;   image[line][1]=PORTA;  
           image[line][2]=PORTA;   image[line][2]=PORTA;   image[line][2]=PORTA;  
           image[line][3]=PORTA;   image[line][3]=PORTA;   image[line][3]=PORTA;  
           image[line][4]=PORTA;   image[line][4]=PORTA;   image[line][4]=PORTA;  
           image[line][5]=PORTA;   image[line][5]=PORTA;   image[line][5]=PORTA;  
           image[line][6]=PORTA;   image[line][6]=PORTA;   image[line][6]=PORTA;  
           image[line][7]=PORTA;   image[line][7]=PORTA;   image[line][7]=PORTA;  
           image[line][8]=PORTA;   image[line][8]=PORTA;   image[line][8]=PORTA;  
           image[line][9]=PORTA;   image[line][9]=PORTA;   image[line][9]=PORTA;  
           image[line][10]=PORTA;  image[line][10]=PORTA;  image[line][10]=PORTA;
           image[line][11]=PORTA;  image[line][11]=PORTA;  image[line][11]=PORTA;  
           image[line][12]=PORTA;  image[line][12]=PORTA;  image[line][12]=PORTA;  
           image[line][13]=PORTA;  image[line][13]=PORTA;  image[line][13]=PORTA;  
           image[line][14]=PORTA;  image[line][14]=PORTA;  image[line][14]=PORTA;  
           image[line][15]=PORTA;  image[line][15]=PORTA;  image[line][15]=PORTA;  
           image[line][16]=PORTA;  image[line][16]=PORTA;  image[line][16]=PORTA;  
           image[line][17]=PORTA;  image[line][17]=PORTA;  image[line][17]=PORTA;  
           image[line][18]=PORTA;  image[line][18]=PORTA;  image[line][18]=PORTA;  
           image[line][19]=PORTA;  image[line][19]=PORTA;  image[line][19]=PORTA;  
           image[line][20]=PORTA;  image[line][20]=PORTA;  image[line][20]=PORTA;  
           image[line][21]=PORTA;  image[line][21]=PORTA;  image[line][21]=PORTA; 
           image[line][22]=PORTA;  image[line][22]=PORTA;  image[line][22]=PORTA;  
           image[line][23]=PORTA;  image[line][23]=PORTA;  image[line][23]=PORTA;  
           image[line][24]=PORTA;  image[line][24]=PORTA;  image[line][24]=PORTA;  
           image[line][25]=PORTA;  image[line][25]=PORTA;  image[line][25]=PORTA;  
           image[line][26]=PORTA;  image[line][26]=PORTA;  image[line][26]=PORTA;  
           image[line][27]=PORTA;  image[line][27]=PORTA;  image[line][27]=PORTA;  
           image[line][28]=PORTA;  image[line][28]=PORTA;  image[line][28]=PORTA;  
           image[line][29]=PORTA;  image[line][29]=PORTA;  image[line][29]=PORTA;  
           image[line][30]=PORTA;  image[line][30]=PORTA;  image[line][30]=PORTA;  
           image[line][31]=PORTA;  image[line][31]=PORTA;  image[line][31]=PORTA;  
           image[line][32]=PORTA;  image[line][32]=PORTA;  image[line][32]=PORTA;
           image[line][33]=PORTA;  image[line][33]=PORTA;  image[line][33]=PORTA;  
           image[line][34]=PORTA;  image[line][34]=PORTA;  image[line][34]=PORTA;  
           image[line][35]=PORTA;  image[line][35]=PORTA;  image[line][35]=PORTA;  
           image[line][36]=PORTA;  image[line][36]=PORTA;  image[line][36]=PORTA;  
           image[line][37]=PORTA;  image[line][37]=PORTA;  image[line][37]=PORTA;  
           image[line][38]=PORTA;  image[line][38]=PORTA;  image[line][38]=PORTA;  
           image[line][39]=PORTA;  image[line][39]=PORTA;  image[line][39]=PORTA;  
           image[line][40]=PORTA;  image[line][40]=PORTA;  image[line][40]=PORTA;  
           image[line][41]=PORTA;  image[line][41]=PORTA;  image[line][41]=PORTA;  
           image[line][42]=PORTA;  image[line][42]=PORTA;  image[line][42]=PORTA;  
           image[line][43]=PORTA;  image[line][43]=PORTA;  image[line][43]=PORTA;   
           image[line][44]=PORTA;  image[line][44]=PORTA;  image[line][44]=PORTA;  
           image[line][45]=PORTA;  image[line][45]=PORTA;  image[line][45]=PORTA;  
           image[line][46]=PORTA;  image[line][46]=PORTA;  image[line][46]=PORTA;  
           image[line][47]=PORTA;  image[line][47]=PORTA;  image[line][47]=PORTA;  
           image[line][48]=PORTA;  image[line][48]=PORTA;  image[line][48]=PORTA;  
           image[line][49]=PORTA;  image[line][49]=PORTA;  image[line][49]=PORTA;  
           image[line][50]=PORTA;  image[line][50]=PORTA;  image[line][50]=PORTA;  
           image[line][51]=PORTA;  image[line][51]=PORTA;  image[line][51]=PORTA;  
           image[line][52]=PORTA;  image[line][52]=PORTA;  image[line][52]=PORTA;  
           image[line][53]=PORTA;  image[line][53]=PORTA;  image[line][53]=PORTA;  
           image[line][54]=PORTA;  image[line][54]=PORTA;  image[line][54]=PORTA;
           image[line][55]=PORTA;  image[line][55]=PORTA;  image[line][55]=PORTA;  
           image[line]56[]=PORTA;  image[line][56]=PORTA;  image[line][56]=PORTA;  
           image[line][57]=PORTA;  image[line][57]=PORTA;  image[line][57]=PORTA;  
           image[line][58]=PORTA;  image[line][58]=PORTA;  image[line][58]=PORTA;  
           image[line][59]=PORTA;  image[line][59]=PORTA;  image[line][59]=PORTA;  
           image[line][60]=PORTA;  image[line][60]=PORTA;  image[line][60]=PORTA;  
           image[line][61]=PORTA;  image[line][61]=PORTA;  image[line][61]=PORTA;  
           image[line][62]=PORTA;  image[line][62]=PORTA;  image[line][62]=PORTA;  
           image[line][63]=PORTA;  image[line][63]=PORTA;  image[line][63]=PORTA;  
           image[line][64]=PORTA;  image[line][64]=PORTA;  image[line][64]=PORTA;  
           image[line][65]=PORTA;  image[line][65]=PORTA;  image[line][65]=PORTA;
           image[line][66]=PORTA;  image[line][66]=PORTA;  image[line][66]=PORTA;  
           image[line][67]=PORTA;  image[line][67]=PORTA;  image[line][67]=PORTA;  
           image[line][68]=PORTA;  image[line][68]=PORTA;  image[line][68]=PORTA;  
           image[line][69]=PORTA;  image[line][69]=PORTA;  image[line][69]=PORTA;  
           image[line][70]=PORTA;  image[line][70]=PORTA;  image[line][70]=PORTA;  
           image[line][71]=PORTA;  image[line][71]=PORTA;  image[line][71]=PORTA;  
           image[line][72]=PORTA;  image[line][72]=PORTA;  image[line][72]=PORTA;  
           image[line][73]=PORTA;  image[line][73]=PORTA;  image[line][73]=PORTA;  
           image[line][74]=PORTA;  image[line][74]=PORTA;  image[line][74]=PORTA;  
           image[line][75]=PORTA;  image[line][75]=PORTA;  image[line][75]=PORTA;  
           image[line][76]=PORTA;  image[line][76]=PORTA;  image[line][76]=PORTA;
           image[line][77]=PORTA;  image[line][77]=PORTA;  image[line][77]=PORTA;  
           image[line][78]=PORTA;  image[line][78]=PORTA;  image[line][78]=PORTA;  
           image[line][79]=PORTA;  image[line][79]=PORTA;  image[line][79]=PORTA;  
                     
         
          */      
     
     
     
      }
     
     
     
     
      TrueLine++;                              //完成了一行的实际 采集 实际采样行数加一 
     }
       
       
       
       
                                     
   LineCount++;                                 //实际行数加一  
   
   if(LineCount>=Line_max||TrueLine>=Row_max)
   
     {
     
      SampleLock=0;                //开采样锁 现在没有在采样  
      ProcessLock=1;               //打开处理锁 防止 场中断 抢占 这一帧未处理的图像  
      PIEP_PIEP7=0;                //关行中断 
     
     
     }
        
     
   
     


}
  


