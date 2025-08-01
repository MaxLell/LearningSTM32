/*
 * Button.h
 *
 *  Created on: Aug 1, 2025
 *      Author: MaximilianLell
 */

#ifndef BUTTON_BUTTON_H_
#define BUTTON_BUTTON_H_

#include "../../Utils/common_types.h"

typedef enum {
  E_BUTTON_STATE_INVALID = 0, // Invalid state
  E_BUTTON_STATE_RELEASED = 1,
  E_BUTTON_STATE_PRESSED = 2,
} Button_State_e;

typedef enum {
  E_BUTTON_POLARITY_INVALID = 0, // Invalid polarity
  E_BUTTON_POLARITY_ACTIVE_LOW,  // Button pressed = GPIO low (pull-up)
  E_BUTTON_POLARITY_ACTIVE_HIGH, // Button pressed = GPIO high (pull-down)
} Button_Polarity_e;

typedef struct {
  Button_State_e eButtonState;
  Button_Polarity_e ePolarity;
  void *pGpioPort;
  u16 u16GpioPin;
} Button_Config_t;

Button_State_e Button_GetState(Button_Config_t *inout_pButton);

#endif /* BUTTON_BUTTON_H_ */
