/*
 * user_app.c
 *
 *  Created on: Jul 28, 2025
 *      Author: MaximilianLell
 */

#ifndef USER_MAIN_C_
#define USER_MAIN_C_

#include "../../Core/Inc/main.h"
#include "../../Utils/CommonTypes.h"
#include "../BlinkyLed/BlinkyLed.h"
#include "../Button/Button.h"
#include "../IsrHandler/IsrHandler.h"
#include "../Profiler/Profiler.h"

#define MAX_NOF_BUTTON_PRESSES (3U)

static BlinkyLed_Config_t tBlinkyLed;
static Button_Config_t tButton;
static IsrHandler_Entry_t atIsrVectorTable[E_ISR_ID_LAST];
static u8 u8ButtonPressedCounter = 0;

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

  // Configure the IsrHandler to the EXTI Button Interrupt
  IsrHandler_Init(atIsrVectorTable, E_ISR_ID_LAST);
  IsrHandler_RegisterIsr(E_ISR_ID_BUTTON_EXTI, (IsrCallback_t)Button_ExtiIsr,
                         (void *)&tButton);

  // Start the Profiler
  Profiler_Init();
}

void UserMain_Loop() {
  bool bButtonWasPressed = Button_WasPressed(&tButton);
  if (true == bButtonWasPressed) {

    u8ButtonPressedCounter++;
    BlinkyLed_Toggle(&tBlinkyLed);
    HAL_Delay(100);

    if (MAX_NOF_BUTTON_PRESSES == u8ButtonPressedCounter) {
      IsrHandler_UnregisterIsr(E_ISR_ID_BUTTON_EXTI);
    }
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
