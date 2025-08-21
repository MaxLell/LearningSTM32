/*
 * OutputHandler.c
 *
 * Created on: August 13, 2025
 * Author: Maximilian Lell
 */

#include "OutputHandler.h"
#include "../../Core/Inc/main.h"
#include "../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"
#include "../BlinkyLed/BlinkyLed.h"
#include "../InterfaceButton/InterfaceButton.h"

BlinkyLed_Config_t tBlinkyLed = {0};

void OutputHandler_Init()
{
	tBlinkyLed.pGpioPort = BLINKY_LED_GPIO_Port;
    tBlinkyLed.u16GpioPin = BLINKY_LED_Pin;
    tBlinkyLed.eLedState = E_BLINKY_LED_OFF;
}

void OutputHandler_Loop()
{
    static bool bLongPressDetected = false;
    InterfaceButton_Event_e eEvent = InterfaceButton_getEvent();
    switch (eEvent)
    {
    case E_INTERFACE_BUTTON_EVENT_PRESSED:
        BlinkyLed_Enable(&tBlinkyLed);
        break;
    case E_INTERFACE_BUTTON_EVENT_LONG_PRESSED:
        bLongPressDetected = true;
        break;
    case E_INTERFACE_BUTTON_EVENT_RELEASED:
        BlinkyLed_Disable(&tBlinkyLed);
        bLongPressDetected = false;
        break;
    default:
        break;
    }

    if (bLongPressDetected)
    {
        BlinkyLed_Toggle(&tBlinkyLed);
        osDelay(50);
    }
    else
    {
        osDelay(1);
    }
}
