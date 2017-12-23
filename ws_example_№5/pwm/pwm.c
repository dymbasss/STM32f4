#include "pwm.h"

// Pin_8 - Pin_9 - Pin_10
#define L_PIN_RED GPIO_Pin_8
#define L_PIN_GREEN GPIO_Pin_9
#define L_PIN_BLUE GPIO_Pin_10

// Button_left - Button_right
#define B_LEFT GPIO_Pin_0
#define B_RIGHT GPIO_Pin_1

//------------------------------------------------------------------------

void c_led(void) // RGB_LED
{
  GPIO_InitTypeDef  led_init_struct;
  
  /* Enable peripheral clock for led port */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);
  
  /* Init leds */
  led_init_struct.GPIO_Pin = L_PIN_RED | L_PIN_GREEN | L_PIN_BLUE;
  led_init_struct.GPIO_Mode = GPIO_Mode_AF;
  led_init_struct.GPIO_OType = GPIO_OType_PP;
  led_init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  led_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOA, &led_init_struct);

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  /* Init leds */
  led_init_struct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15;
  led_init_struct.GPIO_Mode = GPIO_Mode_OUT;
  led_init_struct.GPIO_OType = GPIO_OType_PP;
  led_init_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  led_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_Init(GPIOD, &led_init_struct);
  // GPIO_SetBits(GPIOD,GPIO_Pin_12 | GPIO_Pin_14 | GPIO_Pin_15);
}

//-----------------------------------------------------------------------

void c_timer(uint16_t PERIOD)
{
  TIM_TimeBaseInitTypeDef  t_init_struct;

  TIM_TimeBaseStructInit(&t_init_struct);
  
  /* Enable peripheral clock for timer */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  /* Init timer */
  t_init_struct.TIM_Period = PERIOD; // Period = timer_tick_freq / PWN_freq - 1
  t_init_struct.TIM_Prescaler = 168 - 1; // timer_tick_freq = TIMx_default_freq / (prescaler + 1)
  t_init_struct.TIM_CounterMode = TIM_CounterMode_Up;
  t_init_struct.TIM_ClockDivision = 0;
  TIM_TimeBaseInit(TIM1, &t_init_struct);
  TIM_Cmd(TIM1, ENABLE);

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  /* Init timer */
  t_init_struct.TIM_Period = 1000 - 1;
  t_init_struct.TIM_Prescaler = 84 - 1;
  t_init_struct.TIM_ClockDivision = 0;
  t_init_struct.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &t_init_struct);
  /*Interruption on up-dating*/
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
}

//-----------------------------------------------------------------------

void c_nvic(void)
{
  NVIC_InitTypeDef t_nvic_init_struct;
  
  t_nvic_init_struct.NVIC_IRQChannel = TIM2_IRQn;
  t_nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
  t_nvic_init_struct.NVIC_IRQChannelSubPriority = 1;
  t_nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&t_nvic_init_struct);
}

//-----------------------------------------------------------------------

void c_pwm(void)
{
  TIM_OCInitTypeDef oc_init_struct;
  
  oc_init_struct.TIM_Pulse = 0;    // (timer_period + 1) * DUTY_CYCLE) / 100 - 1
  oc_init_struct.TIM_OCMode = TIM_OCMode_PWM1;
  oc_init_struct.TIM_OutputState = TIM_OutputState_Enable;
  oc_init_struct.TIM_OCPolarity = TIM_OCPolarity_Low;
  
  TIM_OC1Init(TIM1, &oc_init_struct);
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_OC2Init(TIM1, &oc_init_struct);
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_OC3Init(TIM1, &oc_init_struct);
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

//-----------------------------------------------------------------------

void c_button(void) // BUTTON L & R
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
  b_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
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
}

//-----------------------------------------------------------------------
