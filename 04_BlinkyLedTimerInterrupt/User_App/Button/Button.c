/*
 * Button.c
 *
 *  Created on: Aug 1, 2025
 *      Author: MaximilianLell
 */
#include "Button.h"
#include "../../Core/Inc/main.h"
#include "../../Utils/CommonTypes.h"
#include "../../Utils/CustomAssert.h"

#include <stdio.h>

#define LONG_PRESS_PERIOD_MS 1000

void Button_VerifyArguments(Button_Config_t *inout_pButton) {
  // Verify that the Button configuration is valid
  ASSERT(NULL != inout_pButton);
  ASSERT(NULL != inout_pButton->pGpioPort);
  ASSERT(0 != inout_pButton->u16GpioPin);
  ASSERT(E_BUTTON_POLARITY_INVALID != inout_pButton->ePolarity);
}

Button_PinState_e Button_GetPinState(Button_Config_t *inout_pButton) {
  Button_VerifyArguments(inout_pButton);

  // Get the current Button State
  GPIO_PinState ePinState =
      HAL_GPIO_ReadPin(inout_pButton->pGpioPort, inout_pButton->u16GpioPin);

  // Determine the Button State based on the configured polarity
  if (E_BUTTON_POLARITY_ACTIVE_LOW == inout_pButton->ePolarity) {
    inout_pButton->eButtonState = (GPIO_PIN_RESET == ePinState)
                                      ? E_BUTTON_STATE_PRESSED
                                      : E_BUTTON_STATE_RELEASED;
  } else {
    inout_pButton->eButtonState = (GPIO_PIN_SET == ePinState)
                                      ? E_BUTTON_STATE_PRESSED
                                      : E_BUTTON_STATE_RELEASED;
  }
  return inout_pButton->eButtonState;
}

void Button_TimIsr(Button_Config_t *inout_pButton) {
  ASSERT(inout_pButton);
  // Update the Debounced State of the Button
  Button_GetDebouncedState(inout_pButton);
  return;
}

Button_Event_e Button_GetLastEvent(Button_Config_t *const inout_pButton) {
  Button_VerifyArguments(inout_pButton);
  Button_Event_e eLastEvent = inout_pButton->eLastButtonEvent;
  return eLastEvent;
}

void Button_ClearLastEvent(Button_Config_t *const inout_pButton) {
  Button_VerifyArguments(inout_pButton);
  inout_pButton->eLastButtonEvent = E_BUTTON_EVENT_INVALID;
}

/**
 * Taken from https://www.ganssle.com/debouncing-pt2.htm
 */
void Button_GetDebouncedState(Button_Config_t *const inout_ptButton) {
  ASSERT(inout_ptButton);

  // Work with local copies due to better readability
  u32 u32BitState = inout_ptButton->tDebounceFlags.u32BitState;
  Button_PinState_e ePinState = Button_GetPinState(inout_ptButton);
  bool bButtonPressed = (ePinState == E_BUTTON_STATE_PRESSED);

  // Shift one bit, if the button is pressed otherwise shift a zero (happens by
  // default)
  u32BitState = u32BitState << 1;
  if (bButtonPressed) {
    u32BitState |= 0x00000001;
  }

  u16 u16LongPressState = inout_ptButton->tDebounceFlags.u16LongPressState;
  bool bLongPressTriggered = inout_ptButton->tDebounceFlags.bLongPressTriggered;
  inout_ptButton->eLastButtonEvent = E_BUTTON_EVENT_INVALID;

  switch (u32BitState) {
  case 0x0000FFFF: { // Short Press -> 16 Msec consistent shifting of ones
    // Clear the current long button press progress so that it does not carry
    // over to the next button press
    bLongPressTriggered = false;
    u16LongPressState = 0;
    inout_ptButton->eLastButtonEvent = E_BUTTON_EVENT_PRESSED;
  } break;

  case 0xFFFF0000: { // Button Released -> Zeros are shifted in (16 Msec
                     // consistent shifting of zeros)
    // Clear the current long button press progress so that it does not carry
    // over to the next button press
    bLongPressTriggered = false;
    u16LongPressState = 0;
    inout_ptButton->eLastButtonEvent = E_BUTTON_EVENT_RELEASED;
  } break;

  case 0xFFFFFFFF: { // Long Press -> 32 Msec consistent shifting of ones
                     // Button is held down
    inout_ptButton->eLastButtonEvent = E_BUTTON_EVENT_NO_EVENT;
    if (bLongPressTriggered == false) {
      // The button needs to be held down for the long press duration, so that
      // a real user-settable longpress can be detected
      u16LongPressState++;

      if (u16LongPressState == LONG_PRESS_PERIOD_MS) {
        // Clear the current long button press progress so that it does not
        // carry over to the next button press
        bLongPressTriggered = true;
        u16LongPressState = 0;
        inout_ptButton->eLastButtonEvent = E_BUTTON_EVENT_LONG_PRESSED;
      }
    }
  } break;

  default:
    inout_ptButton->eLastButtonEvent = E_BUTTON_EVENT_NO_EVENT;
    break;
  }

  // Update the parsed entries
  inout_ptButton->tDebounceFlags.u32BitState = u32BitState;
  inout_ptButton->tDebounceFlags.u16LongPressState = u16LongPressState;
  inout_ptButton->tDebounceFlags.bLongPressTriggered = bLongPressTriggered;

  ASSERT(inout_ptButton->eLastButtonEvent != E_BUTTON_EVENT_INVALID);

  return;
}
