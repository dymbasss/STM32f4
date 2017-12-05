#include "main.h"
#include "all_struct.h"

int main(void)
{
  
  uint16_t RGB[] = {L_PIN_RED, L_PIN_GREEN, L_PIN_BLUE};
  int i, j = 0;

  c_led();
  
  while (1)
  {
	  /* Switch LED on */
	  GPIO_ResetBits(GPIOA, /*L_PIN_1*/ RGB[j]);
	  for (i=0; i < SWITCH_DELAY; i++)
	  {
	    /* empty cycle */
	  }

	  /* Switch LED off */
	  GPIO_SetBits(GPIOA, /*L_PIN_2*/ RGB[j]);
	  for (i=0; i < SWITCH_DELAY_2; i++)
	  {
	    /* empty cycle */
	  }
	  
	    if  (j >= 2) // R -> G -> B
		{
		  j = 0;
		}
	      else
		{
		  j++;
		}
	   
	    if  (j <= 0)  // R -> B -> G
		{
		  j = 2;
		}
	      else
		{
		  j--;
		}

  }
}
