/*
 * blinky_led.h
 *
 *  Created on: Jul 30, 2025
 *      Author: MaximilianLell
 */

#ifndef BLINKYLED_BLINKYLED_H_
#define BLINKYLED_BLINKYLED_H_

#include "../../Utils/common_types.h"

typedef enum { E_BLINKY_LED_OFF = 0, E_BLINKY_LED_ON = 1 } BlinkyLed_State_e;

typedef struct {
  BlinkyLed_State_e eLedState;
  void *pGpioPort;
  u16 u16GpioPin;
} BlinkyLed_Config_t;

void BlinkyLed_Enable(BlinkyLed_Config_t *inout_pSelf);

void BlinkyLed_Disable(BlinkyLed_Config_t *inout_pSelf);

void BlinkyLed_Toggle(BlinkyLed_Config_t *inout_pSelf);

#endif /* BLINKYLED_BLINKYLED_H_ */
