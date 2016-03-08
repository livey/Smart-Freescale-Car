 #include "includes.h" 
 
 
 
 
 /*******************clock settting ***********************/     

  /*******************use the pll busclock is 60M*****/
 
                             // #define _DISABLE_COP() _ENABLE_COP(0x00) /* COP is disabled if period is 0 */
                             //#define EnableInterrupts   {__asm CLI;}
                             //#define DisableInterrupts  {__asm SEI;}
    /*the pll settings */   
    
  void Busclock_init(void){
    
    
                         
                            //osc=16M
    COPCTL=0X00;           //disable the watch dog 
    IRQCR &= 0xbf;         //IRQCR.6(IRQEN) disable the total interrupt 
                        
       
    CLKSEL=0X00;            //disengage PLL to system  the systmen clk is osc 
    PLLCTL_PLLON=0;         //turn off PLL     
                           
                             // note that the synr and refdv postdiv is can write only be pll_on=0   
    SYNR =(0xc0 | 0x0f);    // synr=vcoreq(11)+syndiv(001110)                    
    REFDV=(0x40 | 0x03);    // reffrq(01)+ refdiv(000011);  Fref=Fosc/(refdiv+1);
   
    POSTDIV=0x00;           // Fpll=Fvco/(2*postdiv)=120M    fvco=2*Fosc*(syndiv+1)/(refdiv+1); =120M
                            // Fbus=Fpll/2;      60M       
    
    PLLCTL_PLLON=1;        // turn on the pll clk 
    
    while(!CRGFLG_LOCK);   //when pll is steady ,then use it;
    
    CLKSEL_PLLSEL =1;       //engage PLL to system; 
 
   /****If it is necessary to test the bus_clock  *///               
      
           //ECLKCTL = 0x60;      ECLKCTL = neclk+cclk2+div[5:0]   
    
    
    
}

 
 
 
 
 
    
     /*** the Serial Communication Interface (SCI) Settings **************/
     
                              //the source of the baudrate is bus_clock 
     /*
          [SCIBDH,SCIBDL]=IREN+TNP1+TNP0+[SBR12:SBR0]  IREN=0       Disable the redir
                                                                baudrate=busclok/(32*sbr[]); 
                                                            
                                                             1 Enable the reir 
                                                                baudrate=busclock/(16*sbr[]); 
           
          [SCIDH,SCIDL]={receive or transfer data};
          SCICR1=[loops,sciswai,rsrc,m,wake,ilt,pe,pt]     workmode  check enable or even or od chck 
          SCICR2=[TIE,TCIE,RIE,ILIE,TE,RE,RWU,SBK]           
          SCISR1=[ ,TC ,RDRF , , , , , ]
          
    
     */
     
void Sci_init(void) {       
       
        SCI1BD=0x1a0;    //baud=9600    baud          the busclock is about 60.2M        188 for usb to serialport 
        SCI1CR1=0X00;    //8BIT no check                                                 190 for the blue tooth 
        SCI1CR2=0X0C;    //enable trasfer and receive 
        
        
               

}


void Sci_write(uint8 ch) {

  while(!(SCI1SR1&0X80));
    SCI1DRH=0;
    SCI1DRL=ch; 
}

uint8 Sci_read(void) {

     if(SCI1SR1_RDRF==1) {
   
      SCI1SR1_RDRF=1;
      return SCI1DRL;
      
   
   }
 

}




 
                    /*the pwm settings*/    
    
     
    /****************************************************
       PPOLx=0
                duty=((PMWPERX-PWMDTYX)/PWMPERX)*100%
       PPOLX=1  
                duty=((PWMDTY/PWMPER)/PWMPER)*100%   
      *************************************************** 
      
        CAE=0  left aligned output 
               
               Pwmperiod=channelclk*pwmprp
        CAE=1  ceter aligned output 
         
               Pwmperiod=channelclk*pwmprp*2          
     
        the source of the clk is from busclock 
       
      ***************************************************/ 

void Pwm_init(void){
  
       PWME_PWME1=0X00;
       PWME_PWME3=0X00;       //the pwm enable first disable and then erase the data below  
       PWME_PWME2=0X00;
       PWME_PWME4=0X00;
       PWME_PWME5=0X00;          
       
       PWMPOL_PPOL1=1;         //decide the duty of the pwm 
       PWMPOL_PPOL2=1;         //the  output polarity 0---low  1---high
       PWMPOL_PPOL3=1;         //the  output polarity 0---low  1---high
       PWMPOL_PPOL4=1;         //the  output polarity 0---low  1---high
       PWMPOL_PPOL5=1;         //the  output polarity 0---low  1---high
       
       PWMCLK_PCLK1=1;
       PWMCLK_PCLK2=1;         // bbaabbaa  b----0 sb----1          0,1-4,5 ===a 
       PWMCLK_PCLK3=1;         // bbaabbaa  b----0 sb----1          2,3-6,7====b
       PWMCLK_PCLK4=1;         // bbaabbaa  a----0 sa----1 
       PWMCLK_PCLK5=1;         // bbaabbaa  a----0 sa----1 
       
                    
       PWMPRCLK=0X11;         //clkb(a)=busclk/(2^n)    the clka and  clkb prediving of busclk  
                              // x.pkb2.pkb1.pkb0.x.pka2.pka1,pka0     clkb(a)=64M/(2^1)=32M 
                                                                     
       PWMCAE_CAE1=0;         //decide the period of the pwm 
       PWMCAE_CAE2=0;
       PWMCAE_CAE3=0;
       PWMCAE_CAE4=0;
       PWMCAE_CAE5=0;
       
        
       PWMCTL=0X10;           //the cout of the pwmclk    select if the pp0(2,4,6) connect with pp1(3,5,7) 
       
       PWMCTL_CON01=1; 
                                       
       
       PWMSCLA=16;            //the scla(b)clk=clka(b)/(2*n);      sclb(a)=32M/(2*16)=1M 
       PWMSCLB=16;
                                            
      // PWMPER0=20000>>8;       //   1M/20,000   =50
      // PWMPER1=20000&0x00ff;
      
       PWMPER01=20000;
       PWMPER2=100;           //the period of the count of the pwm   1M/100=10K 
       PWMPER3=100;
       PWMPER4=100;
       PWMPER5=100;
       
       
             
      
       PWMDTY01=Direction_mid;          //the duty cnts  of the pwm
       
       PWMDTY2=0;
       PWMDTY3=0;
       PWMDTY4=0;   
       PWMDTY5=0;
                           
      
      
       PWME_PWME1=1;
       PWME_PWME3=1;           //the pwm enable first disable and then erase the data below  
       PWME_PWME2=1;
       PWME_PWME4=1;
       PWME_PWME5=1;
    
   
}








void Port_init(void) {

    
   
   
                            //data regist   
    DDRA=0x00;              //data direction register porta     the camera data input 
    
    DDRB=0X00;              // input the count 
    
    DDRT_DDRT4=1;            // the clear input 
    
    
    DDRT_DDRT1=0;
    DDRT_DDRT3=0;
    DDRT_DDRT5=0;
    DDRT_DDRT6=0;
    
    
    
    
    
    
    PTT_PTT4=1;  
    PTT_PTT4=0;
    PTT_PTT4=1; 
     
    
    
    
    
     
                        //see page 73 table 2-3
        
     /*get the vsync*/
             
    PIEJ_PIEJ7=1;         /*the interrupt enable   (1)*/
    PPSJ_PPSJ7=0;         /*select the rising(1) or fall edge(0) signal*/ 
    DDRJ_DDRJ7=0;         //the direction register input (0)  output (1)     
    PERJ_PERJ7=0;         // the pull up enable(1) disable(0) 
 
 
   /* get the Href interrupt */  
   
    PIEP_PIEP7=0;
    PPSP_PPSP7=1;
    DDRP_DDRP7=0;
    PERP_PERP7=0;
      
      
    


}



/*************** The counter initial************/
 void Counter_init(){
 
 
                            // TSCR1|=0X80;
     
       PACTL=0x40;           //0+PAEN+PAMOD+PEDGE+ CLK1+CLK0+PAOVI+PAI using the pt7/ico7 for counting 
                                             //    1     0    1      0    0   0     0
                                                                     

                             // PACNT  is the counter
 
 
 }




void System_init(void) {

  uint8 zhuangtai=0;
  
  
   Busclock_init();
   Port_init();
   Pwm_init();
   Sci_init();
   Counter_init();
   
   
   zhuangtai=PTT_PTT1+(PTT_PTT3<<1);
   
   
   Sci_write(zhuangtai);
  
  switch(zhuangtai){
    
    case (0) : MAX_SPEED=60;
               MIN_SPEED=20;
                       break;
    case (1) : MAX_SPEED=70;
                MIN_SPEED=30;
                break;
    case (2) :  MAX_SPEED=70;
                MIN_SPEED=30;
                break;
    case(3)  :
                MAX_SPEED=80;
                MAX_SPEED=20;
                break;
                
    default :    MAX_SPEED=80;
                 MIN_SPEED=20;
                 break;            
  
   
   
  }
   
   
   
}








  

 