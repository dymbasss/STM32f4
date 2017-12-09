#include "main.h"

// Pin_8 - Pin_9 - Pin_10
#define L_PIN_RED GPIO_Pin_8
#define L_PIN_GREEN GPIO_Pin_9
#define L_PIN_BLUE GPIO_Pin_10

// Button_left - Button_right
#define B_LEFT GPIO_Pin_0
#define B_RIGHT GPIO_Pin_1

static uint16_t RGB[] = {L_PIN_RED, L_PIN_GREEN, L_PIN_BLUE};
static uint16_t j;
static int button_left;
static int button_right;

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
  GPIO_Init(GPIOA, &led_init_struct);
  GPIO_SetBits(GPIOA, L_PIN_RED | L_PIN_GREEN | L_PIN_BLUE);
  return 0;
}

//------------------------------------------------------------------------

static int c_button(void) // BUTTON L & R
{
  GPIO_InitTypeDef b_init_struct;
  NVIC_InitTypeDef b_nvic_init_struct;
  EXTI_InitTypeDef b_exti_init_struct;
  
   /* Enable peripheral clock for buttons port */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  /* Init button */
  b_init_struct.GPIO_Pin = B_LEFT | B_RIGHT;
  b_init_struct.GPIO_Mode = GPIO_Mode_IN;
  b_init_struct.GPIO_OType = GPIO_OType_PP;
  b_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
  b_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &b_init_struct);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource0);
  b_exti_init_struct.EXTI_Line = EXTI_Line0;
  b_exti_init_struct.EXTI_LineCmd = ENABLE;
  b_exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;
  b_exti_init_struct.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_Init(&b_exti_init_struct);

  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource1);
  b_exti_init_struct.EXTI_Line = EXTI_Line1;
  EXTI_Init(&b_exti_init_struct);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, DISABLE);
	    
  b_nvic_init_struct.NVIC_IRQChannel = EXTI0_IRQn;
  b_nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0x00;
  b_nvic_init_struct.NVIC_IRQChannelSubPriority = 0x00;
  b_nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&b_nvic_init_struct);

  b_nvic_init_struct.NVIC_IRQChannelSubPriority = 0x01;
  b_nvic_init_struct.NVIC_IRQChannel = EXTI1_IRQn;
  NVIC_Init(&b_nvic_init_struct);
  return 0;
}

//-----------------------------------------------------------------------

static int c_timer(void)
{
  TIM_TimeBaseInitTypeDef  t_init_struct;
  NVIC_InitTypeDef t_nvic_init_struct;
  
  /* Enable peripheral clock for timer */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  /* Init timer */
  t_init_struct.TIM_Period = 1000000 - 1;
  t_init_struct.TIM_Prescaler = 84 - 1;
  t_init_struct.TIM_ClockDivision = 0;
  t_init_struct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &t_init_struct);
  /*Interruption on up-dating*/
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  /* On */ 
  TIM_Cmd(TIM2, ENABLE);

  t_nvic_init_struct.NVIC_IRQChannel = TIM2_IRQn;
  t_nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
  t_nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
  t_nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&t_nvic_init_struct);
  
  return 0;
}

//-----------------------------------------------------------------------


void EXTI0_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
      EXTI_ClearITPendingBit(EXTI_Line0);
      button_right = 1;
      button_left = 0;
    }
}

void EXTI1_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
      EXTI_ClearITPendingBit(EXTI_Line1);

      button_right = 0;
      button_left = 1;
    }
}

void color_RGB_LEFT(void)
{
  if (button_left == 0)
    {
      GPIO_SetBits(GPIOA, RGB[j]);
      j++;
      if (j >= 3) j = 0;
      GPIO_ResetBits(GPIOA, RGB[j]);
    }
}

void color_RGB_RIGHT(void)
{
  if (button_right == 0)
    {
      GPIO_SetBits(GPIOA, RGB[j]);
      if (j <= 0) j = 3;
      j--;
      GPIO_ResetBits(GPIOA, RGB[j]);
    }
    }

void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
      TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
      
      color_RGB_LEFT();
      color_RGB_RIGHT();
    }
}

int main(void)
{
  j = 0;
  button_left = 1;
  button_right = 1;
  c_led();
  c_button();
  c_timer();
  
  while (1)
    {
    }
}
    
