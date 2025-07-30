/*
 * blinky_led.c
 *
 *  Created on: Jul 30, 2025
 *      Author: MaximilianLell
 */

#include "BlinkyLed.h"

#include "custom_assert.h"
#include "main.h"

void BlinkyLed_Enable(BlinkyLed_Config_t *inout_pSelf) {
  ASSERT(inout_pSelf);
  ASSERT(inout_pSelf->pGpioPort);
  HAL_GPIO_WritePin((GPIO_TypeDef *)inout_pSelf->pGpioPort,
                    (uint16_t)inout_pSelf->u16GpioPin, GPIO_PIN_SET);
  inout_pSelf->eLedState = E_BLINKY_LED_ON;
}

void BlinkyLed_Disable(BlinkyLed_Config_t *inout_pSelf) {
  ASSERT(inout_pSelf);
  ASSERT(inout_pSelf->pGpioPort);
  HAL_GPIO_WritePin((GPIO_TypeDef *)inout_pSelf->pGpioPort,
                    (uint16_t)inout_pSelf->u16GpioPin, GPIO_PIN_RESET);
  inout_pSelf->eLedState = E_BLINKY_LED_OFF;
}

void BlinkyLed_Toggle(BlinkyLed_Config_t *inout_pSelf) {
  ASSERT(inout_pSelf);
  ASSERT(inout_pSelf->pGpioPort);
  inout_pSelf->eLedState = !inout_pSelf->eLedState;
  HAL_GPIO_WritePin((GPIO_TypeDef *)inout_pSelf->pGpioPort,
                    (uint16_t)inout_pSelf->u16GpioPin,
                    (int)inout_pSelf->eLedState);
}
