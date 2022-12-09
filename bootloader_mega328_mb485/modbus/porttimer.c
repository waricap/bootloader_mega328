/*
 * FreeModbus Libary: ATMega168 Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.4 2006/09/03 11:53:10 wolti Exp $
 */

/* ----------------------- AVR includes -------------------------------------*/
#include <avr/io.h>
#include <avr/interrupt.h>

/* ----------------------- Platform includes --------------------------------*/
//#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "../modbus/mb.h"
#include "../modbus/mbport.h"


/* ----------------------- Static variables ---------------------------------*/
extern uint16_t   usTimerOCRADelta;

/* ----------------------- Start implementation -----------------------------*/



inline void vMBPortTimersEnable(  )
{
    TCNT1 = 0x0000;
    if( usTimerOCRADelta > 0 )
    {
        TIMSK1 |= (1<< OCIE1A);
        OCR1A = usTimerOCRADelta;
    }

    TCCR1B |= ((1<< CS12) | (1<< CS10));
}




