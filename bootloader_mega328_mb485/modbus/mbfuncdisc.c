 /*
  * FreeRTOS Modbus Libary: A Modbus serial implementation for FreeRTOS
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
  */



/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbframe.h"
#include "mbproto.h"
#include "mbconfig.h"
#define _BV(bit)  (1 << (bit))

/* ----------------------- Defines ------------------------------------------*/
#define MB_PDU_FUNC_READ_ADDR_OFF           ( MB_PDU_DATA_OFF )
#define MB_PDU_FUNC_READ_DISCCNT_OFF        ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READ_SIZE               ( 4 )
#define MB_PDU_FUNC_READ_DISCCNT_MAX        ( 0x07D0 )

/* ----------------------- Static functions ---------------------------------*/
eMBException    prveMBError2Exception( eMBErrorCode eErrorCode );

/* ----------------------- Start implementation -----------------------------*/

#if MB_FUNC_READ_COILS_ENABLED > 0

eMBException eMBFuncReadDiscreteInputs( UCHAR * pucFrame, USHORT * usLen )  //  (  2 ) //(0x02) Ч чтение значений из нескольких дискретных входов (Read Discrete Inputs).
{
    return eStatus;
}

#endif
