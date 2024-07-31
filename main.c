/*********************************************************************
*                    SEGGER Microcontroller GmbH                     *
*                        The Embedded Experts                        *
**********************************************************************

-------------------------- END-OF-HEADER -----------------------------

File    : main.c

USING STM32F407VET6 board:

SWD interface
PE13 - output LED1

*/
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>
#include <stdlib.h>

/****************************func************************************/
void hwInit(void){
  SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOEEN);
  SET_BIT(GPIOE->MODER, GPIO_MODER_MODER13_0);
}

void vTask1(void * pvParameters){
  for(;;){
    SET_BIT(GPIOE->BSRR, GPIO_BSRR_BS13);
    vTaskDelay(1000);
    SET_BIT(GPIOE->BSRR, GPIO_BSRR_BR13);
    vTaskDelay(1000);
  }
  vTaskDelete(NULL);
}

/****************************main************************************/

int main(void) {
  hwInit();

  xTaskCreate(vTask1, "vTask1", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  vTaskStartScheduler();

  for(;;);
}

/*************************** End of file ****************************/
