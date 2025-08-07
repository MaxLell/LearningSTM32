/*
 * blinky_led.c
 *
 *  Created on: Jul 30, 2025
 *      Author: MaximilianLell
 */

#include "BlinkyLed.h"

#include "custom_assert.h"
#include "main.h"

/**
 * @brief Verifies the validity of LED configuration parameters
 *
 * This function performs runtime validation of the LED configuration
 * structure to ensure all required parameters are properly initialized.
 *
 * @param[in] inout_pLed Pointer to LED configuration structure to verify
 *
 * @pre inout_pLed must point to a valid BlinkyLed_Config_t structure
 *
 * @note This function will trigger an assertion failure if any parameter
 *       is invalid, which may halt program execution in debug builds
 *
 * @warning This function should be called before any LED operations
 *          to prevent undefined behavior
 */
void BlinkyLed_VerifyArguments(BlinkyLed_Config_t *inout_pLed) {
  ASSERT(inout_pLed);
  ASSERT(inout_pLed->pGpioPort);
  ASSERT(inout_pLed->eLedState <= E_BLINKY_LED_ON);
}

/**
 * @brief Turns on the LED and updates the configuration state
 *
 * This function sets the GPIO pin to high level (GPIO_PIN_SET) to turn on
 * the LED and updates the internal state to reflect the change.
 *
 * @param[in,out] inout_pLed Pointer to LED configuration structure
 *                           - Input: GPIO port and pin configuration
 *                           - Output: Updated eLedState to E_BLINKY_LED_ON
 *
 * @pre inout_pLed must be properly initialized with valid GPIO parameters
 * @pre GPIO peripheral must be initialized and configured as output
 *
 * @post LED is physically turned on (GPIO pin set to high)
 * @post eLedState is updated to E_BLINKY_LED_ON
 *
 * @note This function assumes active-high LED configuration
 * @warning Calling this function with invalid parameters will trigger
 * assertions
 */
void BlinkyLed_Enable(BlinkyLed_Config_t *inout_pLed) {
  BlinkyLed_VerifyArguments(inout_pLed);
  HAL_GPIO_WritePin((GPIO_TypeDef *)inout_pLed->pGpioPort,
                    (u16)inout_pLed->u16GpioPin, GPIO_PIN_SET);
  inout_pLed->eLedState = E_BLINKY_LED_ON;
}

/**
 * @brief Turns off the LED and updates the configuration state
 *
 * This function sets the GPIO pin to low level (GPIO_PIN_RESET) to turn off
 * the LED and updates the internal state to reflect the change.
 *
 * @param[in,out] inout_pLed Pointer to LED configuration structure
 *                           - Input: GPIO port and pin configuration
 *                           - Output: Updated eLedState to E_BLINKY_LED_OFF
 *
 * @pre inout_pLed must be properly initialized with valid GPIO parameters
 * @pre GPIO peripheral must be initialized and configured as output
 *
 * @post LED is physically turned off (GPIO pin set to low)
 * @post eLedState is updated to E_BLINKY_LED_OFF
 *
 * @note This function assumes active-high LED configuration
 * @warning Calling this function with invalid parameters will trigger
 * assertions
 */
void BlinkyLed_Disable(BlinkyLed_Config_t *inout_pLed) {
  BlinkyLed_VerifyArguments(inout_pLed);
  HAL_GPIO_WritePin((GPIO_TypeDef *)inout_pLed->pGpioPort,
                    (u16)inout_pLed->u16GpioPin, GPIO_PIN_RESET);
  inout_pLed->eLedState = E_BLINKY_LED_OFF;
}

/**
 * @brief Toggles the LED state between on and off
 *
 * This function inverts the current LED state and updates the GPIO pin
 * accordingly. If the LED is currently on, it will be turned off, and
 * vice versa.
 *
 * @param[in,out] inout_pLed Pointer to LED configuration structure
 *                           - Input: GPIO port, pin, and current state
 *                           - Output: Updated eLedState (inverted)
 *
 * @pre inout_pLed must be properly initialized with valid GPIO parameters
 * @pre GPIO peripheral must be initialized and configured as output
 * @pre eLedState must contain a valid current state
 *
 * @post LED physical state is inverted (on→off or off→on)
 * @post eLedState is updated to reflect the new state
 *
 * @note This function uses boolean inversion on the enum state
 * @note Assumes active-high LED configuration
 * @warning Calling this function with invalid parameters will trigger
 * assertions
 */
void BlinkyLed_Toggle(BlinkyLed_Config_t *inout_pLed) {
  BlinkyLed_VerifyArguments(inout_pLed);
  inout_pLed->eLedState = !inout_pLed->eLedState;
  HAL_GPIO_WritePin((GPIO_TypeDef *)inout_pLed->pGpioPort,
                    (u16)inout_pLed->u16GpioPin, (int)inout_pLed->eLedState);
}
