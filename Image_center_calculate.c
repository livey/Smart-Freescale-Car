#include "includes.h"

  //#define Threshhold    (0x60)


uint8 CenterLine[RealRow]={0};
uint8 DeadLine=RealRow-1;
uint8 StartLine=0;
uint8 *MapPoint=&ImageBuffer[0][0];


  
  /*****图像二值化处理****/   
                                           
void Binarate(void){

        uint16 ii;
        MapPoint=&ImageBuffer[0][0];
        
    for(ii=0;ii<RealRow*RealColumn;ii++) {
    
      if(*MapPoint>ThreshHold)
         *MapPoint=0;
      else *MapPoint=1;
      
      MapPoint++;
    
     }
    

}


     

  


 
    



      /*****中心线提取利用连续性*****/ 
 
/*--------------------------------------------
函数： Calculate  
目的： 对中心线进行巡线 
输入： 整个图像缓存 
输出： 中心线坐标  

错误： 1、初始阶段的的巡线没有找到要防死锁      
----------------------------------------------*/      
      
      
      
      
       

void Calculate(void){

       uint8 FindFirst=0; 
       uint8 m=0;
       uint8 findleft=0;
     
       int8 left=0;
       int8 right=0;
       int8 left_temp;
       int8 right_temp;
       uint8 ii,jj;
       int16 Right_line=RealColumn-9;
       int16 Left_line=0;
       int8  lostline=0;
       
       DeadLine=0;
       StartLine=0;
      
      
      
      

  /*因为前几行很可能是白线，或者不连续点所以应该多搜索 前面几行全搜索 很后面策略不一样 */

	while(!FindFirst)                                   //   插值法求 前一行的坐标
    {
			for(ii=Left_line;ii<Right_line;ii++)                     // 略去 边缘几个点
			{
				  if(ImageBuffer[m][ii]==0  && ImageBuffer[m][ii+1]==1 )     // 如果 由"0" 变为  "1"则找到了 左边缘点
                    {

						findleft=1;
						left=ii;

					}

			    	else if(ImageBuffer[m][ii]==1 &&  ImageBuffer[m][ii+1]==0  )   // 如果由 1 变为 0 则找到了 右边缘点
                                {
						right=ii;
						if(findleft)                        //如果 有了左边缘点

						{
							if((right-left)>=6 && (right-left)<13  )   //过滤过粗过细的线
                                                        {

									CenterLine[m]=(right+left)>>1;
									FindFirst=1;                          //下一个右边沿的到来必定有左边沿的更新
								  StartLine=m; 
									break;


								}
						}

					}
					
				

			}
			
   	if(m>=5){
   	    DeadLine=0;
 		    m=RealRow;                    //防止产生死锁   
 			   break;
   	}
    	findleft=0;
			m++;              //如果没有找到  则到下一行寻找
		}//end of while(findfirst);  

   



	/*采用连续性 寻找 后面行数的中心线*/
	
	for(jj=m;jj<RealRow-1;jj++)
	{
		findleft=0;                                   //没有找到 第一个边缘点
	//	right_temp=right;
  //	left_temp=left;
		CenterLine[jj]=(left+right)>>1;               // 为了连续性 默认中心点即为上一次中心点
    
    Left_line= CenterLine[jj]+7*jj/10-50;
    
      if(Left_line<0)  Left_line=0;
      
    Right_line=CenterLine[jj]-7*jj/10+50;  
      
        if(Right_line>109) Right_line=109;
        
        
  if(left-7<Left_line||right+8>=Right_line) {
  
                                     //检测到边缘 则退出 
    goto haha;
  }

		for(ii=left-7;ii<right+8;ii++)				  // 连续性 扩大点范围找点
		{
			if(ImageBuffer[jj][ii]==0  &&  ImageBuffer[jj][ii+1]==1)                 //找到了左边的点
            {
					findleft=1;
					left_temp=ii;

				}
			else if(ImageBuffer[jj][ii]==1 && ImageBuffer[jj][ii+1]==0)                 //找到了右边点
         {
					right_temp=ii;	            							  //防止了开始即为有一个黑到白的情况 和 有了前面的白到黑 必然有黑到白的过程
					if((right_temp-left_temp)>=1  && (right_temp-left_temp)<12 && findleft)                  
				    	{
						CenterLine[jj]=(right_temp+left_temp)>>1;
						DeadLine=jj;
						left=left_temp;
						right=right_temp;


						break;

				    	}
			 	}

     	if(ii==right+7) {left-=2;right+=2;lostline++; 
     	
     	
     	
     	
                                    ////////////////////////// 
                                    
     	                                   if(lostline>4) 
     	                              ///////////////////////////                
     	                                     goto  haha;
     	
     	                                        break;}    //如果没有找到中心线则扩大搜索范围 
				                                            //因为很可能是遇到了转弯的虚线 

		}


	}

haha:              //中心线滤波

   for(ii=StartLine+2;ii<DeadLine+1;ii++)
	    

			  CenterLine[ii]=(5*CenterLine[ii-2]+5*CenterLine[ii-1]+6*CenterLine[ii])>>4;
 
     



}

/*-----------------------------------------------
函数:  ImageCenterCalculate 
目的： 函数中心线提取
输入： 采集的图样
输出： 中心线数组 CenterLine    结尾标志  DeadLine
错误： 
-----------------------------------------------*/




void  ImageCenterCalculate(void) {

 Binarate();
 
 Calculate(); 
 
 

}
