/*
 * FreeModbus Libary: ATMega168 Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *   - Initial version and ATmega168 support
 * Modfications Copyright (C) 2006 Tran Minh Hoang:
 *   - ATmega8, ATmega16, ATmega32 support
 *   - RS485 support for DS75176
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
 * File: $Id: portserial.c,v 1.6 2006/09/17 16:45:53 wolti Exp $
 */

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <avr/signal.h>

//#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "../modbus/mb.h"
#include "../modbus/mbport.h"

#define UART_BAUD_RATE          9600
#define F_CPU 16000000UL
#define UART_BAUD_CALC(UART_BAUD_RATE, F_CPU)   ( ( F_CPU ) / ( ( UART_BAUD_RATE ) * 16UL ) - 1 )
#define UART_UCSRB  UCSR0B

//
void  vMBPortSerialEnable( bool xRxEnable, bool xTxEnable )
{
    UCSR0B |= ((1<< TXEN0) | (1<< TXCIE0));

    if( xRxEnable )
    {
        UCSR0B |= ((1<< RXEN0) | (1<< RXCIE0));
    }
    else
    {
        UCSR0B &= ~((1<< RXEN0) | (1<< RXCIE0));
    }

    if( xTxEnable )
    {
        UCSR0B |= ((1<< TXEN0) | (1<< UDRE0));
        PORTC |= (1<< PORTC3);;
    }
    else
    {
        UCSR0B &= ~(1<< UDRE0);
    }
}


