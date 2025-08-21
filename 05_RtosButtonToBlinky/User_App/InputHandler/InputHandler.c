/*
 * InputHandler.c
 *
 * Created on: August 13, 2025
 * Author: Maximilian Lell
 */

#include "../../Core/Inc/main.h"
#include "../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"
#include "../Button/Button.h"
#include "InputHandler.h"

static Button_Config_t tUserButton = { 0 };
static DataModel_t    *g_ptButtonEvent;

void InputHandler_Init( DataModel_t *const inout_ptButtonEvent )
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

    g_ptButtonEvent = inout_ptButtonEvent;
}

void InputHandler_Loop()
{
    static uint32_t tick = 0;
    if( tick == 0 )
    {
        tick = osKernelGetTickCount();
    }

    Button_TimIsr( &tUserButton );

    Button_Event_e eButtonEvent = Button_GetLastEvent( &tUserButton );
    u32            u32Size = (u32)sizeof( eButtonEvent );

    if( E_BUTTON_EVENT_NO_EVENT != eButtonEvent )
    {
        DataModel_Write( g_ptButtonEvent, &eButtonEvent, u32Size );

        Button_ClearLastEvent( &tUserButton );
    }

    // 1ms tick for button polling (precise)
    tick += 1;
    osDelayUntil( tick );
}