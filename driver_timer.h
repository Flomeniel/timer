#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
/**
  * @brief   Initialiser une GPIO pour ressortir une clock
  */
typedef struct
{
  uint32_t RCC_APB1Periph;				/*!< Specifier le timer  (voir la fonction RCC_APB1PeriphClockCmd(-)) .
											Ce parametre peut prendre une valeur de @defgroup RCC_APB1_Peripherals */

  uint32_t RCC_AHB1Periph;				/*!< Specifier le GpioX pour la clock(voir la fonction RCC_AHB1PeriphClockCmd(-)).
											Ce parametre peut prendre pour valeur @defgroup RCC_AHB1_Peripherals */

  GPIO_TypeDef* GPIOx;					/*!< Specifier le GpioX pour la clock(voir la fonctionGPIO_Init(-)).
											Ce parametre peut prendre pour valeur @addtogroup Peripheral_declaration */

  uint16_t GPIO_PinSource;				/*!< Specifier la broche de la Gpio(voir la GPIO_PinAFConfig(-)).
											Ce parametre peut prendre pour valeur @defgroup GPIO_Pin_sources */

  uint8_t GPIO_AF;						/*!< Specifier la broche utilise pour la foncion timer.
											Ce parametre peut prendre pour valeur @ref AF 1 selection */

}GPIO_InitConfTime;




void InitGpioxTimer(GPIO_InitConfTime* Gpio_Init, GPIO_InitTypeDef* GPIO_InitStruct2, FunctionalState NewState);









