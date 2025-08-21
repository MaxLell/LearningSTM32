/*
 * InterfaceButton.c
 *
 * Created on: August 13, 2025
 * Author: Maximilian Lell
 */

#include "InterfaceButton.h"

static InterfaceButton_Event_e eCurrentEvent = E_INTERFACE_BUTTON_EVENT_INVALID;

void InterfaceButton_setEvent(InterfaceButton_Event_e in_peEvent)
{
    eCurrentEvent = in_peEvent;
}

InterfaceButton_Event_e InterfaceButton_getEvent(void) { return eCurrentEvent; }
