/**
  ******************************************************************************
  * @file    driver_timer.c
  * @author  Florent Dumazel Clement Souyri Gabriel Aygalenq
  * @version V1.0.0
  * @date    30-Septembre-2014
  * @bref    Ce fichier fournit des fonctions pour gerer
  *          les fonctionnalitées du timer:
  *            - Initialiser les GPIO pour Timer
  *            - Initialiser les Timer
  *            - Lancer et arreter les Timer
  *
  *
  *
  *          ===================================================================
  *                                 Comment utiliser ce driver
  *          ===================================================================
  *
  *          Ce driver necessite 4 etapes pour fonctionner:
  *
  *           1. Initialiser le Gpio sur lequel sortir le Timer:
  *   void InitGpioxTimer(GPIO_InitConfTime* Gpio_InitTimer, GPIO_InitTypeDef* GPIO_InitStructure, FunctionalState NewState)
  *				- Configurer la structure GPIO_InitConfTime.
  *				- Configurer la structure GPIO_InitTypeDef.
  *				- Activer les Timer.
  *
  *           2. Initialiser et configurer le Timer:
  *   void InitTimer(TIM_TypeDef* TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period, uint8_t TIM_RepetitionCounter)
  *				- Selectionner le Timer (TM1, TM2..).
  *				- Selectionner le Timer (TM1, TM2..).
  *             - Clock sortie = 65 Mhz /( (PSC+1)*(ARR+1)*(RCR+1) ).
  *
  *           3. Configurer le PWM:
  *   void InitPwm(TIM_TypeDef* TIMx, uint16_t TIM_OCMode, uint32_t TIM_Pulse);
  *              - Selectionner le Timer (TM1, TM2..).
  *              - Selectionner le mode de fonctionnement.
  *              - Selectionner le pourcentage d'etat haut.
  *
  *           4. To get the level of a pin configured in input mode use GPIO_ReadInputDataBit()
  *	  void StartOrStopTimer(TIM_TypeDef* TIMx, FunctionalState NewState);
  *				 - Lancer ou arreter le Timer.
  *
  *  @endverbatim
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_tim.h>
#include <stm32f4xx.h>
#include <stm32f4xx_gpio.h>
#include <driver_timer.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Configure, initialise le Timer et Gpio de sortie.
  * @note   Remplir la structure GPIO_InitConfTime*
  * 		Remplir la structure GPIO_InitTypeDef*
  * @param  Gpio_InitTimer: Pointer qur la structure GPIO_InitConfTime qui
  * 			contient les parametres du Timer et de la Gpio.
  * @param  GPIO_InitStruct: Pointer sur la stucture GPIO_InitTypeDef qui
  * 			contient les parametres de la broche GPIO.
  * @param  NewState: Nouvel etat d'activation
  *          Ce parametre peut etre: ENABLE or DISABLE.
  * @retval None
  */
void InitGpioxTimer(GPIO_InitConfTime* Gpio_InitTimer, GPIO_InitTypeDef* GPIO_InitStructure, FunctionalState NewState)
{

	RCC_APB1PeriphClockCmd(Gpio_InitTimer->RCC_APB1Periph, NewState);

	RCC_AHB1PeriphClockCmd(Gpio_InitTimer->RCC_AHB1Periph, NewState);

	GPIO_Init(Gpio_InitTimer->GPIOx, &(*GPIO_InitStructure));

	GPIO_PinAFConfig(Gpio_InitTimer->GPIOx, Gpio_InitTimer->GPIO_PinSource, Gpio_InitTimer->GPIO_AF);
}

/**
  * @brief  Configure le timer.
  * @note   Remplir la structure GPIO_InitConfTime*
  * 		Remplir la structure GPIO_InitTypeDef*
  * @param  Gpio_InitTimer: Pointer qur la structure GPIO_InitConfTime qui
  * 			contient les parametres du Timer et de la Gpio.
  * @param  GPIO_InitStruct: Pointer sur la stucture GPIO_InitTypeDef qui
  * 			contient les parametres de la broche GPIO.
  * @param  NewState: Nouvel etat d'activation
  *          Ce parametre peut etre: ENABLE or DISABLE.
  * @retval None
  */
void InitTimer(TIM_TypeDef* TIMx, uint16_t TIM_Prescaler, uint32_t TIM_Period, uint8_t TIM_RepetitionCounter)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

	TIM_TimeBaseStructure.TIM_Prescaler =TIM_Prescaler;// psc
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = TIM_Period;// arr
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=TIM_RepetitionCounter;// rcc

	TIM_TimeBaseInit(&(*TIMx), &TIM_TimeBaseStructure);
}

void InitPwm(TIM_TypeDef* TIMx, uint16_t TIM_OCMode, uint32_t TIM_Pulse)
{

	TIM_OCInitTypeDef       TIM_OCInitStructure;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = TIM_Pulse;//(PreCalPeriod * Duty_Cycle) / 100;

	TIM_OC1Init(&(*TIMx), &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(&(*TIMx), TIM_OCPreload_Enable);

	TIM_ARRPreloadConfig(&(*TIMx), ENABLE);
}

void StartOrStopTimer(TIM_TypeDef* TIMx, FunctionalState NewState)
{
	TIM_Cmd(&(*TIMx), NewState);
}


