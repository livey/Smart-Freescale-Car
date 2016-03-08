#include"includes.h"
/*-----------------------------------
函数：AtuoStop 
目的：检测起跑线 自动停止  
输入：检测到的线的第二行  只在起跑线的第二行检测 
输出：直接进入死循环 ，刹车 
思想：遵循  黑-白-黑-白-黑 的特征线     

错误：
------------------------------------*/

/****************图样*****************
mode  :    0   1  2  3  4   5   6             

image : 00000ffff000fff0000fff00000
          白   黑 白 黑  白 黑  白     
**************************************/



uint8 stoped;

void AutoStop(void) {
    
      uint8 ii,jj;
      uint8 left=0;
      uint8 mode=0;              //状态      
      uint8 b2w=0,w2b=0;
 
      uint8 buffer[RealColumn];
 
      uint8 left_edge,right_edge;
      uint16 kk;
 
 if(DeadLine>11){
 
 
  
 
 
  
                                           
  for(jj=0;jj<20;jj++) {                    // 连续检测10行，以防止 漏检测 10行数据对应20cm满足最快速度要求 
    
      
     for(ii=0;ii<RealColumn-10;ii++) {
        
        if(ImageBuffer[jj][ii]||ImageBuffer[jj+1][ii]||ImageBuffer[jj+2][ii])
             buffer[ii]=1;
       
        else buffer[ii]=0;
     
     }
      
     
   
     mode=0; 
     
     
     
     left_edge= CenterLine[jj]+7*jj/10-50;
        if(left_edge < 0) left_edge=0;
                 
        
     right_edge=CenterLine[jj]-7*jj/10+50;
        if(right_edge>(RealColumn-10))  right_edge=RealColumn-10;
     
      
    for(ii=left_edge;ii<right_edge;ii++)    
    {
           
      
       if(buffer[ii]==0 && buffer[ii+1]==1)     //检测到   白-》黑 
       {
            left=ii;
            
            w2b=ii;
       
        switch(mode) 
           {
            case 0: {
           
              mode=1;
              break;
           
                    }
                    
            case 2: {
            
           if(w2b-b2w>=2)
                  mode=3;
             
             
                else  mode=0;
              
              
              break;
                
            }
            
            case 4: {
            
                if(w2b-b2w>=2)
                  mode=5;
            
                 else  mode=0;
                 
                  break;
                  }
             
            default:mode=0;
                    break;  
        
              }
        }
        
          if(buffer[ii]==1 && buffer[ii+1]==0) // 检测到    黑-》白
           {
              b2w=ii;
             
           switch(mode) 
           {
                case 1: {                                     //起跑线宽
                     if((ii-left)>=10)      
                        mode=2;
                    
                       break;
                      }
          
                case 3: {
                       if((ii-left)>=2 && (ii-left)<10)      //跑道宽度 窄一点 
                       
                       
                       
                       mode=4;
                       
                    
                       break;
                    }
                    
                case 5:{
                        if((ii-left)>=10) {                 //起跑线宽
                        
                       if(abs(ExpectDirection)<50) {
                        
                         Motor_left=0;
                         Motor_right=0;
                    SteerDirection=Direction_mid;
                         Motor_left_r=100;
                         Motor_right_r=100;
                         
                         for(kk=0;kk<40000;kk++);
                          for(kk=0;kk<40000;kk++);
                          for(kk=0;kk<40000;kk++);
                          for(kk=0;kk<40000;kk++);
                         Motor_left_r=0;
                         Motor_right_r=0;
                         
                         
                         stoped=1;
                         
                        // print_binarymap();
                        
                        // while(1);                   //结束进入死循环
                         }
                        
                        }       //停止  
                        break;
                    
                       }
                default:  
            
                      mode=0;        
          
             } //end of switch 
      }//end of if  
     
   
    }// end of for ii
  }
   
  
 }//end of if (DeadLine>12);
}//end of function 

 




