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

#define BLINKY_LED_TOGGLE_INTERVAL (50U)

typedef struct {
  BlinkyLed_Config_t *pBlinkyLed;
  Button_Config_t *pButton;
} UserMain_CombinedContext_t;

static BlinkyLed_Config_t tBlinkyLed;
static Button_Config_t tButton;
static IsrHandler_Entry_t atIsrVectorTable[E_ISR_ID_LAST];
static UserMain_CombinedContext_t tCombinedContext;

static void
UserMain_CombinedCallback(UserMain_CombinedContext_t *const inout_ptContext);

void UserMain_Init() {
  // Start the Profiler
  Profiler_Init();

  // Configure the LED
  tBlinkyLed.u16GpioPin = LED2_PIN;
  tBlinkyLed.pGpioPort = LED2_GPIO_PORT;
  tBlinkyLed.eLedState = E_BLINKY_LED_OFF;

  // Configure the Button
  tButton.pGpioPort = USER_BUTTON_GPIO_Port;
  tButton.u16GpioPin = USER_BUTTON_Pin;
  tButton.ePolarity = E_BUTTON_POLARITY_ACTIVE_HIGH;
  tButton.eButtonState = E_BUTTON_STATE_RELEASED;
  tButton.eLastButtonEvent = E_BUTTON_EVENT_INVALID;
  tButton.tDebounceFlags.u32BitState = 0;
  tButton.tDebounceFlags.u16LongPressedMsecCounter = 0;
  tButton.tDebounceFlags.bLongPressTriggered = false;

  // Configure the IsrHandler to the Timer Interrupt
  tCombinedContext.pBlinkyLed = &tBlinkyLed;
  tCombinedContext.pButton = &tButton;

  IsrHandler_Init(atIsrVectorTable, E_ISR_ID_LAST);
  IsrHandler_RegisterIsr(E_ISR_ID_COMBINED_BUTTON_AND_BLINKY_ISR,
                         (IsrCallback_t)UserMain_CombinedCallback,
                         (void *)&tCombinedContext);
}

void UserMain_Loop() {}

void UserMain(void) {
  // Init
  UserMain_Init();

  // Loop
  for (;;) {
    UserMain_Loop();
  }
}

void UserMain_CombinedCallback(
    UserMain_CombinedContext_t *const inout_ptContext) {
  ASSERT(inout_ptContext);

  static volatile u32 u32NofMsecPassed;
  static bool bButtonLongPressed = false;

  // Call the Button ISR
  Button_TimIsr(inout_ptContext->pButton);

  // Parse the Button Event
  Button_Event_e eLastButtonEvent =
      Button_GetLastEvent(inout_ptContext->pButton);

  // Select the action to be taken for said button event
  switch (eLastButtonEvent) {
  case E_BUTTON_EVENT_PRESSED:
    // Do nothing
    break;
  case E_BUTTON_EVENT_LONG_PRESSED:
    // Enable the long press action
    bButtonLongPressed = true;
    u32NofMsecPassed = 0;
    break;
  case E_BUTTON_EVENT_RELEASED:
    // Clear the LED
    BlinkyLed_Disable(inout_ptContext->pBlinkyLed);
    bButtonLongPressed = false;
    break;
  default:
    break;
  }

  Button_ClearLastEvent(inout_ptContext->pButton);

  if (bButtonLongPressed) {
    if (u32NofMsecPassed % BLINKY_LED_TOGGLE_INTERVAL == 0) {
      BlinkyLed_Toggle(inout_ptContext->pBlinkyLed);
    }
  }

  // Make sure there is no variable overrun
  if (0xFFFFFFF0 == u32NofMsecPassed) {
    u32NofMsecPassed = 0;
  } else {
    u32NofMsecPassed++;
  }
}

#endif /* USER_MAIN_C_ */
