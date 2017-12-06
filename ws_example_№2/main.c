#include "main.h"

int main(void)
{
  
  uint16_t RGB[] = {L_PIN_RED, L_PIN_GREEN, L_PIN_BLUE};
  uint32_t timer = 0;
  int j = 0;

  c_led();
  c_button();
  c_timer();
  
  while (1)
    {
      timer = TIM_GetCounter(TIM2);
      
      if (GPIO_ReadInputDataBit(GPIOE, B_LEFT) == 0)
       	{
	  if( timer == 0)
	    {
	      GPIO_ResetBits(GPIOA, RGB[j]);
	    }
	  else if (timer == 999999)
	    {
	      GPIO_SetBits(GPIOA, RGB[j]);
	      
	      if (j >= 2)
		{
		  j = 0;
		}
	      else
		{
		  j++;
		}
	    }
	}
       
      if (GPIO_ReadInputDataBit(GPIOE, B_RIGHT) == 0)
       	{
	  if (timer == 0)
	    {
	      GPIO_ResetBits(GPIOA, RGB[j]);
	    }
	  else if (timer == 999999)
	    {
	      GPIO_SetBits(GPIOA, RGB[j]);
	      
	      if (j <= 0)
		{
		  j = 2;
		}	
	      else
		{
		  j--;
		}
	    }
	    }
    }
}
    
