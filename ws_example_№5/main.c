#include "main.h"
#include "pwm/pwm.h"

#define PWM_FREQ 100 // Hz PWM_freq = timer_tick_freq / (TIM_Period + 1)
#define PERIOD (uint32_t)(1000000 / PWM_FREQ - 1) // 10 kHz -> 8399 tacts

static uint32_t r_value;
static uint32_t g_value;
static uint32_t b_value;

static uint16_t RGB[] = {GPIO_Pin_14, GPIO_Pin_12, GPIO_Pin_15};

static uint16_t j;
static int button_left;
static int button_right;

void next_color_RGB(void)
{ 
  j++;
  if(j >= 3) {j = 0;}
}

void up_color_RGB(void)
{
  if (j == 0)
    {
      r_value += PERIOD * 2 /100;
      if (r_value >= PERIOD) {r_value = 0;}
    }
  if (j == 1)
    {
      g_value += PERIOD * 2 /100;
      if (g_value >= PERIOD) {g_value = 0;}
    }
  if (j == 2)
    {
      b_value += PERIOD * 2 /100;
      if (b_value >= PERIOD) {b_value = 0;}
    }
}

void on_color_RGB(void)
{
  
  GPIO_ResetBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_12 | GPIO_Pin_15);
  
  if (j == 0)                                
    {
      TIM_SetCompare1(TIM1, r_value);
      GPIO_SetBits(GPIOD, RGB[j]);
    }
  else if (j == 1)
    {
      TIM_SetCompare2(TIM1, g_value);
      GPIO_SetBits(GPIOD, RGB[j]);
    }

  else if (j == 2)
    {
      TIM_SetCompare3(TIM1, b_value);
      GPIO_SetBits(GPIOD, RGB[j]);
    }
}

void EXTI0_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
      EXTI_ClearITPendingBit(EXTI_Line0);
      
      button_right = 1;
      button_left = 0;
      
      up_color_RGB();
    }
}

void EXTI1_IRQHandler(void)
{
  if (EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
      EXTI_ClearITPendingBit(EXTI_Line1);
      
      button_right = 0;
      button_left = 1;
      
      next_color_RGB();
    }
}

void TIM2_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)

    {
      TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

      on_color_RGB();
    }
}

int main(void)
{ 
  button_left = 1;
  button_right = 1;
  r_value = 0;
  g_value = 0;
  b_value = 0;
  j = 0;
  
  c_led();
  c_timer(PERIOD);
  c_pwm();
  c_nvic();
  c_button();
  
  while (1)
    {
    }
}
    
