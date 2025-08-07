/*
 * Button.h
 *
 *  Created on: Aug 1, 2025
 *      Author: MaximilianLell
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#include "../../Utils/CommonTypes.h"

/**
 * @brief Button state enumeration.
 */
typedef enum {
  E_BUTTON_STATE_INVALID = 0,
  E_BUTTON_STATE_RELEASED = 1,
  E_BUTTON_STATE_PRESSED = 2,
} Button_State_e;

/**
 * @brief Button polarity enumeration.
 */
typedef enum {
  E_BUTTON_POLARITY_INVALID = 0,
  E_BUTTON_POLARITY_ACTIVE_LOW,
  E_BUTTON_POLARITY_ACTIVE_HIGH,
} Button_Polarity_e;

/**
 * @brief Configuration structure for a button instance.
 *
 * Holds the state, polarity, and hardware configuration for a single button.
 */
typedef struct {
  Button_State_e eButtonState;
  Button_Polarity_e ePolarity;
  void *pGpioPort;
  u16 u16GpioPin;
  bool bExtiIsrWasTriggered;
} Button_Config_t;

/**
 * @brief Reads and updates the current state of the button.
 *
 * Reads the GPIO pin and updates the button state in the configuration
 * structure.
 * @param[in,out] inout_pButton Pointer to the button configuration structure.
 * @return Button_State_e Current button state (pressed or released).
 */
Button_State_e Button_GetState(Button_Config_t *inout_pButton);

bool Button_WasPressed(Button_Config_t *inout_pButton);

/**
 * @brief EXTI interrupt service routine for the button.
 *
 * Should be called from the EXTI ISR to signal a button event.
 * @param[in,out] inout_pButton Pointer to the button configuration structure.
 */
void Button_ExtiIsr(Button_Config_t *inout_pButton);

#endif /* BUTTON_BUTTON_H_ */
