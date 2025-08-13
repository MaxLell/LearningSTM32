/*
 * InterfaceButton.h
 *
 * Created on: August 13, 2025
 * Author: Maximilian Lell
 */

#ifndef INTERFACEBUTTON_H
#define INTERFACEBUTTON_H

typedef enum {
  E_INTERFACE_BUTTON_EVENT_INVALID = -1,
  E_INTERFACE_BUTTON_EVENT_PRESSED,
  E_INTERFACE_BUTTON_EVENT_RELEASED,
  E_INTERFACE_BUTTON_EVENT_LONG_PRESSED,
  E_INTERFACE_BUTTON_EVENT_NO_EVENT,
} InterfaceButton_Event_e;

void InterfaceButton_setEvent(InterfaceButton_Event_e in_peEvent);

InterfaceButton_Event_e InterfaceButton_getEvent(void);

#endif /* INTERFACEBUTTON_H */
