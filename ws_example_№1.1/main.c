#include "main.h"

int main(void)
{
  
  uint16_t RGB[] = {L_PIN_RED, L_PIN_GREEN, L_PIN_BLUE};
  int j = 0;

  c_led();
  c_button();
  
  while (1)
  {

    if(GPIO_ReadInputDataBit(GPIOE, B_LEFT) == 0)
      {
	GPIO_ResetBits(GPIOA, RGB[j]);
	for(int i = 0; i < SWITCH_DELAY; i++)
	  {
	  }
	GPIO_SetBits(GPIOA, RGB[j]);
	for(int i = 0; i < SWITCH_DELAY / 25; i++)
	  {
	  }
	if (j >= 2)
	  {
	    j = 0;
	  }
	else
	  {
	    j++;
	  }
      }
    
    if(GPIO_ReadInputDataBit(GPIOE, B_RIGHT) == 0)
      {
	GPIO_ResetBits(GPIOA, RGB[j]);
	for(int i = 0; i < SWITCH_DELAY; i++)
	  {
	  }
	GPIO_SetBits(GPIOA, RGB[j]);
	for(int i = 0; i < SWITCH_DELAY / 25; i++)
	  {
	  }
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
