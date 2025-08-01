/*
 * user_app.c
 *
 *  Created on: Jul 28, 2025
 *      Author: MaximilianLell
 */

#ifndef USER_MAIN_C_
#define USER_MAIN_C_

#include "BlinkyLed.h"
#include "main.h"


void UserMain(void) {
  // Init
  BlinkyLed_Config_t tBlinkyLed;
  tBlinkyLed.u16GpioPin = LED2_PIN;
  tBlinkyLed.pGpioPort = LED2_GPIO_PORT;
  tBlinkyLed.eLedState = E_BLINKY_LED_OFF;

  // Loop
  for (;;) {
    BlinkyLed_Toggle(&tBlinkyLed);
    HAL_Delay(500);
  }
}

#endif /* USER_MAIN_C_ */
