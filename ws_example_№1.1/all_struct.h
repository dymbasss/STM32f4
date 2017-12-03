#ifndef _ALL_STRUCT_H
#define _ALL_STRUCT_H

// Frequency
#define SWITCH_DELAY 5000000

// Pin_8 - Pin_9 - Pin_10
#define L_PIN_RED GPIO_Pin_8
#define L_PIN_GREEN GPIO_Pin_9
#define L_PIN_BLUE GPIO_Pin_10

// Button_left - Button_right
#define B_LEFT GPIO_Pin_0
#define B_RIGHT GPIO_Pin_1

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

static int c_button(void) // BUTTON L & R
{
  GPIO_InitTypeDef button_init_struct;
   /* Enable peripheral clock for buttons port */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  /* Init button */
  button_init_struct.GPIO_Pin = B_LEFT | B_RIGHT;
  button_init_struct.GPIO_Mode = GPIO_Mode_IN;
  button_init_struct.GPIO_OType = GPIO_OType_PP;
  button_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
  button_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &button_init_struct);
  return 0;
}

//-----------------------------------------------------------------------

#endif

