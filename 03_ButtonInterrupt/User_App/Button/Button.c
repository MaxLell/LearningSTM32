/*
 * Button.c
 *
 *  Created on: Aug 1, 2025
 *      Author: MaximilianLell
 */

#include "common_types.h"

#include "Button.h"
#include "custom_assert.h"
#include "main.h"

/**
 * @brief Verifies the validity of button configuration parameters
 *
 * This function performs runtime validation of the button configuration
 * structure to ensure all required parameters are properly initialized.
 *
 * @param[in] inout_pButton Pointer to button configuration structure to verify
 *
 * @pre inout_pButton must point to a valid Button_Config_t structure
 *
 * @note This function will trigger an assertion failure if any parameter
 *       is invalid, which may halt program execution in debug builds
 *
 * @warning This function should be called before any button operations
 *          to prevent undefined behavior
 */
void Button_VerifyArguments(Button_Config_t *inout_pButton) {
  // Verify that the Button configuration is valid
  ASSERT(NULL != inout_pButton);
  ASSERT(NULL != inout_pButton->pGpioPort);
  ASSERT(0 != inout_pButton->u16GpioPin);
  ASSERT(E_BUTTON_POLARITY_INVALID != inout_pButton->ePolarity);
}

/**
 * @brief Reads the current state of a button and updates the configuration
 *
 * This function reads the GPIO pin state and determines whether the button
 * is currently pressed or released based on the configured polarity.
 * The button state is updated in the configuration structure and returned.
 *
 * @param[in,out] inout_pButton Pointer to button configuration structure
 *                              - Input: GPIO port, pin, and polarity
 * configuration
 *                              - Output: Updated eButtonState field
 *
 * @return Button_State_e Current button state (pressed or released)
 * @retval E_BUTTON_STATE_PRESSED Button is currently being pressed
 * @retval E_BUTTON_STATE_RELEASED Button is currently released
 *
 * @pre inout_pButton must be properly initialized with valid GPIO parameters
 * @pre GPIO peripheral must be initialized and configured
 *
 * @note The function respects the configured polarity:
 *       - ACTIVE_LOW: Button pressed when GPIO reads low
 *       - ACTIVE_HIGH: Button pressed when GPIO reads high
 *
 * @warning Calling this function with invalid parameters will trigger
 * assertions
 */
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

bool Button_WasPressed(Button_Config_t *inout_pButton) {
  Button_VerifyArguments(inout_pButton);

  bool bWasPressed = inout_pButton->bExtiIsrWasTriggered;
  inout_pButton->bExtiIsrWasTriggered = false;
  return bWasPressed;
}

void Button_ExtiIsr(Button_Config_t *inout_pButton) {
  Button_VerifyArguments(inout_pButton);
  inout_pButton->bExtiIsrWasTriggered = true;
}