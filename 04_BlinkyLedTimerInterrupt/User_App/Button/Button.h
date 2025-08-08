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
} Button_PinState_e;

typedef enum {
  E_BUTTON_EVENT_INVALID = -1,
  E_BUTTON_EVENT_PRESSED,
  E_BUTTON_EVENT_RELEASED,
  E_BUTTON_EVENT_LONG_PRESSED,
} Button_Event_e;

/**
 * @brief Button polarity enumeration.
 */
typedef enum {
  E_BUTTON_POLARITY_INVALID = 0,
  E_BUTTON_POLARITY_ACTIVE_LOW,
  E_BUTTON_POLARITY_ACTIVE_HIGH,
} Button_Polarity_e;

typedef struct {
  u16 u16LongPressState;
  u32 u32State;
  bool bLongPressTriggered;
} Button_DebounceFlags_t;

typedef struct {
  Button_PinState_e eButtonState;
  Button_Polarity_e ePolarity;
  Button_Event_e eLastButtonEvent;
  Button_DebounceFlags_t tDebounceFlags;
  void *pGpioPort;
  u16 u16GpioPin;
} Button_Config_t;

void Button_TimIsr(Button_Config_t *const inout_pButton);

void Button_GetDebouncedState(Button_Config_t *const inout_ptButton);

Button_PinState_e Button_GetPinState(Button_Config_t *const inout_pButton);

Button_Event_e Button_GetLastEvent(Button_Config_t *const inout_pButton);

void Button_ClearLastEvent(Button_Config_t *const inout_pButton);

#endif /* BUTTON_BUTTON_H_ */
