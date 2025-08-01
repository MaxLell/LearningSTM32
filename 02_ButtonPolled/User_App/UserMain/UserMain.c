/*
 * user_app.c
 *
 *  Created on: Jul 28, 2025
 *      Author: MaximilianLell
 */

#ifndef USER_MAIN_C_
#define USER_MAIN_C_

#include "BlinkyLed.h"
#include "Button.h"
#include "main.h"

static BlinkyLed_Config_t tBlinkyLed;
static Button_Config_t tButton;

void UserMain_Init() {
	// Configure the LED
  tBlinkyLed.u16GpioPin = LED2_PIN;
  tBlinkyLed.pGpioPort = LED2_GPIO_PORT;
  tBlinkyLed.eLedState = E_BLINKY_LED_OFF;

  // Configure the Button
  tButton.pGpioPort = USER_BUTTON_GPIO_Port;
  tButton.u16GpioPin = USER_BUTTON_Pin;
  tButton.ePolarity = E_BUTTON_POLARITY_ACTIVE_HIGH;
  tButton.eButtonState = E_BUTTON_STATE_RELEASED;
}

void UserMain_Loop() {
  Button_State_e eButtonState = Button_GetState(&tButton);
  if (E_BUTTON_STATE_PRESSED == eButtonState) {
    BlinkyLed_Enable(&tBlinkyLed);
    HAL_Delay(100);
    BlinkyLed_Disable(&tBlinkyLed);
  }
}

void UserMain(void) {
  // Init
  UserMain_Init();

  // Loop
  for (;;) {
    UserMain_Loop();
  }
}

#endif /* USER_MAIN_C_ */
