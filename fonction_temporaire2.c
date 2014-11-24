#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "system_stm32f4xx.h"
#include "fonction_temporaire.h"


#define   APB1_FREQ       42000000                            // Clock driving TIM3
#define   CNT_FREQ        21000000                            // TIM3 counter clock (prescaled APB1)
#define   PWM_FREQ        50000                            // PWM frequency in (320Hz~21MHz) range 8000000  50000
#define   PWM_DC_CH1      50                                  // Channel 1 duty cycle
#define   PWM_DC_CH2      25                                  // Channel 2 duty cycle

#define   TIM_PULSE_CH1    (((PWM_DC_CH1) * (APB1_FREQ)) \
                          / ((PWM_FREQ) * (200)))             // Output Compare 1 reg value
#define   TIM_PULSE_CH2    (((PWM_DC_CH2) * (APB1_FREQ)) \
                          / ((PWM_FREQ) * (200)))             // Output Compare 2 reg value
#define   TIM_PERIOD       (((CNT_FREQ) / (PWM_FREQ))-1)      // Autoreload reg value
#define   TIM_PRESCALER    (((APB1_FREQ) / (CNT_FREQ))-1)     // APB1 prescaler


void RCC_Configuration2(void)
{
  /* --------------------------- System Clocks Configuration -----------------*/
  /* TIM4 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  /* GPIOD clock enable */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
}

void configuration_timer(void)
{

	  TIM_TimeBaseInitTypeDef TIM3_TimeBase;                      // Time Base structure

	  TIM3_TimeBase.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM3_TimeBase.TIM_RepetitionCounter = 0;                        // Not dividing
	  TIM3_TimeBase.TIM_CounterMode   = TIM_CounterMode_Up;       // Upcounting configuration
	  TIM3_TimeBase.TIM_Period        = TIM_PERIOD;               // Autoreload value (ARR)
	  TIM3_TimeBase.TIM_Prescaler     = 0;            // dividing APB1 by 2
	  TIM_TimeBaseInit(TIM3, &TIM3_TimeBase);                     // Initializing Time Base structure

	  TIM_TIxExternalClockConfig(TIM3, TIM_TIxExternalCLK1Source_TI1, TIM_ICPolarity_Rising, 0);
	/*  TIM_OCInitTypeDef       TIM3_OC;                            // Output Compare structure

	  TIM3_OC.TIM_OCMode      = TIM_OCMode_PWM2;                  // Edge-aligned mode
	  //TIM_OCMode_Active
	  TIM3_OC.TIM_OutputState = TIM_OutputState_Enable;           // Enabling the Output Compare state
	  TIM3_OC.TIM_OCPolarity  = TIM_OCPolarity_High;              // Regular polarity (low will inverse it)
	  TIM3_OC.TIM_Pulse       = TIM_PULSE_CH1;                    // Output Compare 1 reg value
	  TIM_OC1Init(TIM3, &TIM3_OC);                                // Initializing Output Compare 1 structure
	  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);          // Disabling Ch.1 Output Compare preload*/

/*	  TIM3_OC.TIM_OutputState = TIM_OutputState_Enable;           // Enabling again in case the values changed
	  TIM3_OC.TIM_Pulse       = TIM_PULSE_CH1;                    // Output Compare 2 reg value
	  TIM_OC2Init(TIM3, &TIM3_OC);                                // Initializing Output Compare 2 structure
	  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Disable);          // Disabling Ch.2 Output Compare preload
	 */
	  TIM_Cmd(TIM3, ENABLE);                                      // Ready, Set, Go!
}

void configuration_gpio(void)
{
	  GPIO_InitTypeDef        gpio_C;                             // GPIOC structure

	  gpio_C.GPIO_Pin   = GPIO_Pin_6 | GPIO_Pin_7;                // Ch.1 (PC6), Ch.2 (PC7)
	  gpio_C.GPIO_Mode  = GPIO_Mode_AF;                           // PWM is an alternative function
	  gpio_C.GPIO_Speed = GPIO_Speed_100MHz;                        // 50MHz
	  gpio_C.GPIO_OType = GPIO_OType_PP;                          // Push-pull
	  gpio_C.GPIO_PuPd  = GPIO_PuPd_UP;                           // Pulling-up
	  GPIO_Init(GPIOC, &gpio_C);                                  // Initializing GPIOC structure
	  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM3);     // Routing TIM3 output to PC6
	  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM3);     // Routing TIM3 output to PC7
}
