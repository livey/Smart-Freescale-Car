#include "includes.h"

uint8 ThreshHold=0x50;

uint8 AutoThresh(uint8 startline) {
     unsigned char max[20]={0};
	   unsigned char min[4]={0xff};

      unsigned char ii,jj;
   	int maxt=0,mint=0;

	for(ii=0;ii<RealColumn;ii++)
		 {
                for(jj=0;jj<20;jj++)
					 {

					     if(max[jj]<ImageBuffer[startline][ii])
					        { max[jj]=ImageBuffer[startline][ii];
						        break;

						    	}

					  }


				for(jj=0;jj<4;jj++)
			    {

					 if(min[jj]>ImageBuffer[startline][ii])
						 { min[jj]=ImageBuffer[startline][ii];break;}

				 	}

		 }


       for(ii=0;ii<20;ii++)
	      	maxt+=max[ii];

       maxt/=20;


	  for(ii=0;ii<4;ii++)
		  mint+=min[ii];

	    mint/=4;



     return((maxt-mint)>>1);
 



}