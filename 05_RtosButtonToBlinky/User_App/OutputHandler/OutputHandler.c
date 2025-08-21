/*
 * OutputHandler.c
 *
 * Created on: August 13, 2025
 * Author: Maximilian Lell
 */

#include "../../Core/Inc/main.h"
#include "../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/cmsis_os2.h"
#include "../../Utils/CustomAssert.h"
#include "../BlinkyLed/BlinkyLed.h"
#include "../Button/Button.h"
#include "OutputHandler.h"

BlinkyLed_Config_t  tBlinkyLed = { 0 };
static bool         g_bIsNotificationPresent = false;
static DataModel_t *g_ptButtonEvent = NULL;

static void OutputHandler_NotificationCallback( void )
{
    g_bIsNotificationPresent = true;
}

static Observer_t g_tObserver = { 0 };

void OutputHandler_Init( DataModel_t *const inout_ptButtonEvent )
{
    // Setup the Blinky LED
    tBlinkyLed.pGpioPort = BLINKY_LED_GPIO_Port;
    tBlinkyLed.u16GpioPin = BLINKY_LED_Pin;
    tBlinkyLed.eLedState = E_BLINKY_LED_OFF;

    g_ptButtonEvent = inout_ptButtonEvent;

    // Add the Notification Callback to the observer
    g_tObserver.pFnNotification = OutputHandler_NotificationCallback;
    g_tObserver.u32Id = 1;
    DataModel_AddObserver( g_ptButtonEvent, &g_tObserver );
}

void OutputHandler_Loop()
{
    static bool bLongPressDetected = false;

    if( true == g_bIsNotificationPresent )
    {
        Button_Event_e eButtonEvent = E_BUTTON_EVENT_INVALID;
        u32            u32Size = 0;
        DataModel_Read( g_ptButtonEvent, &eButtonEvent, &u32Size );
        ASSERT( u32Size == sizeof( Button_Event_e ) );

        switch( eButtonEvent )
        {
        case E_BUTTON_EVENT_PRESSED:
            BlinkyLed_Enable( &tBlinkyLed );
            break;
        case E_BUTTON_EVENT_LONG_PRESSED:
            bLongPressDetected = true;
            break;
        case E_BUTTON_EVENT_RELEASED:
            BlinkyLed_Disable( &tBlinkyLed );
            bLongPressDetected = false;
            break;
        default:
            // Nothing to be done here
            break;
        }
    }

    if( bLongPressDetected )
    {
        BlinkyLed_Toggle( &tBlinkyLed );
        osDelay( 50 );
    }
    else
    {
        osDelay( 1 );
    }
}
