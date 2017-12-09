#include "main.h"

// Frequency
#define SWITCH_DELAY 5000000
#define SWITCH_DELAY_2 10000

// Pin_8 - Pin_9 - Pin_10
#define L_PIN_RED GPIO_Pin_8
#define L_PIN_GREEN GPIO_Pin_9
#define L_PIN_BLUE GPIO_Pin_10

//------------------------------------------------------------------------

static int c_led(void) // RGB_LED
{
  GPIO_InitTypeDef  led_init_struct;
  /* Enable peripheral clock for led port */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 
  /* Init leds */
  led_init_struct.GPIO_Pin = L_PIN_RED | L_PIN_GREEN | L_PIN_BLUE;
  led_init_struct.GPIO_Mode = GPIO_Mode_OUT;
  led_init_struct.GPIO_OType = GPIO_OType_PP;
  led_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
  led_init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL; 
  GPIO_Init(GPIOA, &led_init_struct);
  GPIO_SetBits(GPIOA, L_PIN_RED | L_PIN_GREEN | L_PIN_BLUE);

return 0;
}

//------------------------------------------------------------------------

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
