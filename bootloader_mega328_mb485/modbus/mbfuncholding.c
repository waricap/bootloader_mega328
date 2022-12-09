/* 
 * FreeModbus Libary: A portable Modbus implementation for Modbus ASCII/RTU.
 * Copyright (c) 2006 Christian Walter <wolti@sil.at>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * File: $Id: mbfuncholding.c,v 1.12 2007/02/18 23:48:22 wolti Exp $
 */

/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"

/* ----------------------- Platform includes --------------------------------*/
//#include "../port2/port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbframe.h"
#include "mbproto.h"
#include "mbconfig.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_PDU_FUNC_READ_ADDR_OFF               ( MB_PDU_DATA_OFF + 0)
#define MB_PDU_FUNC_READ_REGCNT_OFF             ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READ_SIZE                   ( 4 )
#define MB_PDU_FUNC_READ_REGCNT_MAX             ( 0x00FF )

#define MB_PDU_FUNC_WRITE_ADDR_OFF              ( MB_PDU_DATA_OFF + 0)
#define MB_PDU_FUNC_WRITE_VALUE_OFF             ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_WRITE_SIZE                  ( 4 )

#define MB_PDU_FUNC_WRITE_MUL_ADDR_OFF          ( MB_PDU_DATA_OFF + 0 )
#define MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF        ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF       ( MB_PDU_DATA_OFF + 4 )
#define MB_PDU_FUNC_WRITE_MUL_VALUES_OFF        ( MB_PDU_DATA_OFF + 5 )
#define MB_PDU_FUNC_WRITE_MUL_SIZE_MIN          ( 5 )
#define MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX        ( 0x00FF )

#define MB_PDU_FUNC_READWRITE_READ_ADDR_OFF     ( MB_PDU_DATA_OFF + 0 )
#define MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF   ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF    ( MB_PDU_DATA_OFF + 4 )
#define MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF  ( MB_PDU_DATA_OFF + 6 )
#define MB_PDU_FUNC_READWRITE_BYTECNT_OFF       ( MB_PDU_DATA_OFF + 8 )
#define MB_PDU_FUNC_READWRITE_WRITE_VALUES_OFF  ( MB_PDU_DATA_OFF + 9 )
#define MB_PDU_FUNC_READWRITE_SIZE_MIN          ( 9 )



/* ----------------------- Start implementation -----------------------------*/

eMBException
eMBFuncWriteMultipleHoldingRegister( uint8_t * pucFrame, uint16_t * usLen )
{
 // если пришла команда записи, 
 // и пакет прошел CRC проверку, 
 // то нефиг выискивать стартовый адрес и длину, они всегда 5 и 65
            if( MB_ENOERR == eMBRegHoldingCB( &pucFrame[MB_PDU_FUNC_WRITE_MUL_VALUES_OFF], 5, 65, MB_REG_WRITE ))
            {
                *usLen = 5;//MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF;
            }
    return MB_EX_NONE;
}




eMBException
eMBFuncReadHoldingRegister( uint8_t * pucFrame, uint16_t * usLen )  //  (  3 )  //(0x03) — чтение значений из нескольких регистров хранения (Read Holding Registers).
{
  //  uint16_t          usRegCount;
    uint8_t          *pucFrameCur;

            /* Set the current PDU data pointer to the beginning. */
            pucFrameCur = &pucFrame[MB_PDU_FUNC_OFF];
            //*usLen = MB_PDU_FUNC_OFF;

            /* First byte contains the function code. */
            *pucFrameCur++ = MB_FUNC_READ_HOLDING_REGISTER;
            //*usLen += 1;

            /* Second byte in the response contain the number of bytes. */
            *pucFrameCur++ = 8; //( uint8_t ) ( 4 * 2 );
            //*usLen += 1;

            /* Make callback to fill the buffer. */
            /* If an error occured convert it into a Modbus exception. */
			eMBRegHoldingCB( pucFrameCur, 1, 4, MB_REG_READ);
//            if(MB_ENOERR == eMBRegHoldingCB( pucFrameCur, 1, 4, MB_REG_READ ))
//            {
                //*usLen += 4 * 2;
				*usLen = 10;
 //           }

    return MB_EX_NONE;
}

