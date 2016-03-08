#include "includes.h"
 


/*---------------------------------------------------------------------
  º¯Êı£º Ö÷º¯Êı
  Ä¿µÄ£º Õû¸öº¯ÊıµÄ³ÌĞòÁ÷£º  
         
         Í¼ÏñºóÌ¨²É¼¯-¡·Í¼ÏñÖĞĞÄÏßÌáÈ¡-¡·Í¼Ïñ·½Ïò¼ÆËã-¡ PID ËÙ¶È·½ÏòÊä³ö
         
  ÊäÈë£º  ÎŞ 
  Êä³ö£º  ÎŞ
  ´íÎó£º  Í¼Ïñ´¦ÀíÍêÁËÓ¦¸Ã´ò¿ª²ÉÑùËø £¬²»È»Ö÷º¯Êı·µ»Ø½Ó×Å´¦Àí  
  
   
  ---------------------------------------------------------------------*/ 

 
 


void main(void) {

 stoped=0;
 

 DisableInterrupts;              /****ÏµÍ³³õÊ¼»¯***/  

 System_init();


 SampleLock=1; 
 ProcessLock=0;
 
 EnableInterrupts;
 
 
 
   
 SteerDirection=Direction_mid;









 
 
 
 while(system_time<120);         //ÏÈÍ£Ö¹Á½Ãë  
  
 Motor_left=100;
 Motor_right=100;                      
   
   
ThreshHold=0x80;    //0x80
  
  
  
while(1) {
  
if(!SampleLock) {               //Èç¹ûÃ»ÓĞÔÚ²ÉÑù Ôò¿ªÊ¼´¦ÀíÍ¼Ïñ  
        
  
     ProcessLock=1; 
       
      
    
    
        
     
 //  if(Sci_read()=='a')
         
  //      print_init_map();
         
     //   print_binarymap();
       
      
     //  ThreshHold=AutoThresh(StartLine);
       
       
       ImageCenterCalculate();   //½øĞĞÍ¼ÏñÖĞĞÄÏßÌáÈ¡ 
   
      
       
      
     // if(Sci_read()=='a')
         
          // print_init_map();
         
      // print_binarymap();
  
    
     // while(Sci_read()!='a');       //´òÓ¡Í¼Ïñ ·µ»ØÊµ¼Ê´¦Àí 
     
   
   
   
   if(system_time>500)          //¼ì²âÆğÅÜÏß  10s Ö®ºó  
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
        
    
       ProcessLock=0;               //¹Ø±Õ´¦ÀíËø  
       SampleLock=1;                //´ò¿ª²ÉÑùËø 
     
   
     }
    
    
   
    
     
     
      // ImageProcess();             //¸ù¾İÍ¼ÏñÌáÈ¡ÖĞĞÄÏßºóµÄÍ¼Ïñ ¼ÆËã ½Ç¶È ºÍ ËÙ¶È      
     //  AutoControl();              //¸ù¾İÖĞĞÄÏß´¦ÀíºóµÃµ½ ½Ç¶È ºÍ ÆÚÍûËÙ¶ÈÖµ½øĞĞ PID ¿ØÖÆ   
    
    
    
}//  end of while(1);


}