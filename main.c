#include <stm32f4xx_gpio.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx.h>
#include "driver_timer.h"

static void delay_long();
static void delay_court();

int main()
{
	SystemCoreClockUpdate();
	SystemInit();
	SystemCoreClockUpdate();
	GPIO_InitConfTime   GPIO_InitStrutureGpioxTimer;

	GPIO_InitStrutureGpioxTimer.RCC_APB1Periph=RCC_APB1Periph_TIM3;
	GPIO_InitStrutureGpioxTimer.RCC_AHB1Periph=RCC_AHB1Periph_GPIOC;
	GPIO_InitStrutureGpioxTimer.GPIOx=GPIOC;
	GPIO_InitStrutureGpioxTimer.GPIO_PinSource=GPIO_PinSource6;
	GPIO_InitStrutureGpioxTimer.GPIO_AF=GPIO_AF_TIM3;


	// Configure PC6-PC9 pins as AF, Pull-Down
	GPIO_InitTypeDef        GPIO_InitStructure;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;

	InitGpioxTimer(&GPIO_InitStrutureGpioxTimer, &GPIO_InitStructure, ENABLE);


	InitTimer(TIM3, 10, 10, 0);


	InitPwm(TIM3, TIM_OCMode_PWM1, 2);

	StartOrStopTimer(TIM3, ENABLE);

while(1)
  {

  }

}
static void delay_long()
{
	double compteur =0;			//on déclare le compteur utilisé dans la temporisation
	for(compteur=0;compteur <0xFF;compteur++){}
}

