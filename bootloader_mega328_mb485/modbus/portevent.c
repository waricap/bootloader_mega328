/*
 */

/* ----------------------- Modbus includes ----------------------------------*/
#include "../modbus/mb.h"
#include "../modbus/mbport.h"

/* ----------------------- Variables ----------------------------------------*/
static eMBEventType eQueuedEvent;
static bool     xEventInQueue = FALSE;

/* ----------------------- Start implementation -----------------------------*/

void xMBPortEventPost( eMBEventType eEvent )
{
    xEventInQueue = TRUE;
    eQueuedEvent = eEvent;
}

bool xMBPortEventGet( eMBEventType * eEvent )
{
    bool            xEventHappened = FALSE;

    if( xEventInQueue )
    {
        *eEvent = eQueuedEvent;
        xEventInQueue = FALSE;
        xEventHappened = TRUE;
    }
    return xEventHappened;
}
