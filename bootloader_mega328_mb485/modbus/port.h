/*
 * FreeModbus Libary: AVR Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *   - Initial version + ATmega168 support
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
 * File: $Id: port.h,v 1.6 2006/09/17 16:45:52 wolti Exp $
 */

#ifndef _PORT_H
#define _PORT_H

/* ----------------------- Platform includes --------------------------------*/

#include <avr/io.h>
#include <avr/interrupt.h>

/* ----------------------- Defines ------------------------------------------*/
#define	INLINE                      inline
#define PR_BEGIN_EXTERN_C           extern "C" {
#define	PR_END_EXTERN_C             }


typedef unsigned long ULONG;
typedef long    LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif


/* ----------------------- RS485 specifics ----------------------------------*/
//#ifdef  RTS_ENABLE

#define RTS_PIN         PORTC3
#define RTS_DDR         DDRC
#define RTS_PORT        PORTC

#define RTS_INIT        \
    do { \
        DDRC |= (1<< PORTC3); \
        PORTC &= ~(1<< PORTC3); \
    } while( 0 );

#define RTS_HIGH        \
    do { \
        PORTC |= (1<< PORTC3); \
    } while( 0 );

#define RTS_LOW         \
    do { \
        PORTC &= ~(1<< PORTC3); \
    } while( 0 );

//#endif

#endif
