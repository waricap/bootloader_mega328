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
 * File: $Id: mb.c,v 1.28 2010/06/06 13:54:40 wolti Exp $
 */

/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"
#include <stdbool.h>
/* ----------------------- Platform includes --------------------------------*/
//#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbconfig.h"
#include "mbframe.h"
#include "mbproto.h"
#include "mbfunc.h"
#include "mbport.h"
#include "mbrtu.h"


/* ----------------------- Static variables ---------------------------------*/

extern uint8_t    ucMBAddress;

bool( *pxMBFrameCBReceiveFSMCur ) ( void );
bool( *pxMBFrameCBTransmitFSMCur ) ( void );

/* An array of Modbus functions handlers which associates Modbus function
 * codes with implementing functions.
 */
//static xMBFunctionHandler xFuncHandlers[2] = {
//    {MB_FUNC_READ_HOLDING_REGISTER,		eMBFuncReadHoldingRegister			},//(  3 ) //(0x03) � ������ �������� �� ���������� ��������� �������� (Read Holding Registers).
//    {MB_FUNC_WRITE_MULTIPLE_REGISTERS,	eMBFuncWriteMultipleHoldingRegister	} //(0x10) � ������ �������� � ��������� ��������� �������� (Preset Multiple Registers)
//};

/* ----------------------- Start implementation -----------------------------*/


eMBErrorCode  eMBPoll( void )
{
    static uint8_t   *ucMBFrame;
    static uint8_t   ucRcvAddress;
    static uint16_t   usLength;

    uint8_t             i;
    eMBErrorCode    eStatus = MB_ETIMEDOUT ; //MB_ENOERR;
    eMBEventType    eEvent;

    xMBPortEventGet( &eEvent ); // ���������, ��� �� ������� ��� �����, ����� ����������� � ���
      switch ( eEvent )
        {
        case EV_READY: // ������ ��������.
            break;

        case EV_FRAME_RECEIVED: // Frame  ������, ��������,  � ���������� ���� �������

            eStatus = eMBRTUReceive( &ucRcvAddress, &ucMBFrame, &usLength ); // ��� ���������� 3 ��������� �� ������, ��� ��� ������� ������, � ������ ������
            if(( eStatus == MB_ENOERR ) & ( ucRcvAddress == ucMBAddress ))//  ���� ����� ������, �������� ������� �����, � ���
            {
               xMBPortEventPost( EV_EXECUTE );
            }
            break;

        case EV_EXECUTE: // ��������� �������.
				if( 0x03 == ucMBFrame[MB_PDU_FUNC_OFF])  // �� �������� ������ ������� ��� �������
					{ eMBFuncReadHoldingRegister( ucMBFrame, &usLength  ); }				// ��� ����� ���� � ����������  �������, ������������ ���������� �� ���� ���������
				else if ( 0x10 == ucMBFrame[MB_PDU_FUNC_OFF])								// �� �������� ������ ������� ��� �������
						{ eMBFuncWriteMultipleHoldingRegister( ucMBFrame, &usLength  ); }	// ��� ����� ���� � ����������  �������, ������������ ���������� �� ���� ���������
				eStatus = eMBRTUSend( ucMBAddress, ucMBFrame, usLength );// �� ���������� �����.
			break;

        case EV_FRAME_SENT: // Frame  ���� ���������.
            break;
        }

    return eStatus ; //MB_ENOERR;
}
