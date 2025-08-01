/*
 * Button.c
 *
 *  Created on: Aug 1, 2025
 *      Author: MaximilianLell
 */

#include "common_types.h"

#include "Button.h"
#include "main.h"
#include "custom_assert.h"

void Button_VerifyArguments(Button_Config_t *inout_pButton) {
  // Verify that the Button configuration is valid
  ASSERT(NULL != inout_pButton);
  ASSERT(NULL != inout_pButton->pGpioPort);
  ASSERT(0 != inout_pButton->u16GpioPin);
  ASSERT(E_BUTTON_POLARITY_INVALID != inout_pButton->ePolarity);
}

Button_State_e Button_GetState(Button_Config_t *inout_pButton) {
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
