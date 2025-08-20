/*
 * InputHandler.c
 *
 * Created on: August 13, 2025
 * Author: Maximilian Lell
 */

#include "InputHandler.h"
#include "../../Core/Inc/main.h"
#include "../Button/Button.h"
#include "../InterfaceButton/InterfaceButton.h"
#include "cmsis_os2.h" // For osDelayUntil

static Button_Config_t tUserButton = {0};

void InputHandler_Init()
{

    // Configure the Button
    tUserButton.pGpioPort = USER_BUTTON_GPIO_Port;
    tUserButton.u16GpioPin = USER_BUTTON_Pin;
    tUserButton.ePolarity = E_BUTTON_POLARITY_ACTIVE_HIGH;
    tUserButton.eButtonState = E_BUTTON_STATE_RELEASED;
    tUserButton.eLastButtonEvent = E_BUTTON_EVENT_INVALID;
    tUserButton.tDebounceFlags.u32BitState = 0;
    tUserButton.tDebounceFlags.u16LongPressedMsecCounter = 0;
    tUserButton.tDebounceFlags.bLongPressTriggered = false;
}

void InputHandler_Loop(void)
{
    static uint32_t tick = 0;
    if (tick == 0)
    {
        tick = osKernelGetTickCount();
    }

    Button_TimIsr(&tUserButton);

    Button_Event_e eButtonEvent = Button_GetLastEvent(&tUserButton);

    switch (eButtonEvent)
    {
    case E_BUTTON_EVENT_PRESSED:
        InterfaceButton_setEvent(E_INTERFACE_BUTTON_EVENT_PRESSED);
        break;
    case E_BUTTON_EVENT_RELEASED:
        InterfaceButton_setEvent(E_INTERFACE_BUTTON_EVENT_RELEASED);
        break;
    case E_BUTTON_EVENT_LONG_PRESSED:
        InterfaceButton_setEvent(E_INTERFACE_BUTTON_EVENT_LONG_PRESSED);
        break;
    default:
        break;
    }

    Button_ClearLastEvent(&tUserButton);

    // 1ms tick for button polling (precise)
    tick += 1;
    osDelayUntil(tick);
}