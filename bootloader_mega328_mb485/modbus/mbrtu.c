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
 * File: $Id: mbrtu.c,v 1.18 2007/09/12 10:15:56 wolti Exp $
 */

/* ----------------------- System includes ----------------------------------*/
#include "stdlib.h"
#include "string.h"
#include <avr/io.h>
/* ----------------------- Platform includes --------------------------------*/
//#include "../port2/port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbrtu.h"
#include "mbframe.h"

#include "mbcrc.h"
#include "mbport.h"

/* ----------------------- Defines ------------------------------------------*/
#define MB_SER_PDU_SIZE_MIN     4       /*!< Minimum size of a Modbus RTU frame. */
#define MB_SER_PDU_SIZE_MAX     256     /*!< Maximum size of a Modbus RTU frame. */
#define MB_SER_PDU_SIZE_CRC     2       /*!< Size of CRC field in PDU. */
#define MB_SER_PDU_ADDR_OFF     0       /*!< Offset of slave address in Ser-PDU. */
#define MB_SER_PDU_PDU_OFF      1       /*!< Offset of Modbus-PDU in Ser-PDU. */

#define F_CPU 16000000UL // Объявление частоты микроконтроллера для макросов _delay_us
#define MB_TIMER_PRESCALER      ( 1024UL )
#define MB_TIMER_TICKS          ( F_CPU / MB_TIMER_PRESCALER )
#define MB_50US_TICKS           ( 20000UL )

/* ----------------------- Type definitions ---------------------------------*/
typedef enum
{
    STATE_RX_INIT,              /*!< Receiver is in initial state. */
    STATE_RX_IDLE,              /*!< Receiver is in idle state. */
    STATE_RX_RCV,               /*!< Frame is beeing received. */
    STATE_RX_ERROR              /*!< If the frame is invalid. */
} eMBRcvState;

typedef enum
{
    STATE_TX_IDLE,              /*!< Transmitter is in idle state. */
    STATE_TX_XMIT               /*!< Transmitter is in transfer state. */
} eMBSndState;

extern uint16_t   usTimerOCRADelta;

/* ----------------------- Static variables ---------------------------------*/
static volatile eMBSndState eSndState;
static volatile eMBRcvState eRcvState= STATE_RX_INIT;

volatile uint8_t  ucRTUBuf[MB_SER_PDU_SIZE_MAX];

static volatile uint8_t *pucSndBufferCur;
static volatile uint16_t usSndBufferCount;

static volatile uint16_t usRcvBufferPos;

/* ----------------------- Start implementation -----------------------------*/

eMBErrorCode eMBRTUReceive( uint8_t * pucRcvAddress, uint8_t ** pucFrame, uint16_t * pusLength )
{
    eMBErrorCode    eStatus = MB_ENOERR;

    cli(); 

    /* Length and CRC check */
    if( ( usRcvBufferPos >= MB_SER_PDU_SIZE_MIN )     && ( usMBCRC16( ( uint8_t * ) ucRTUBuf, usRcvBufferPos ) == 0 ) )
    {
        // Сохраните поле адреса. Все кадры передаются на верхний уровень, и там принимается решение, использовать ли тот или иной кадр.
        *pucRcvAddress = ucRTUBuf[MB_SER_PDU_ADDR_OFF];

        // Общая длина Modbus-PDU равна Modbus-Serial-Line-PDU за вычетом размера поля адреса и контрольной суммы CRC.
        *pusLength = ( uint16_t )( usRcvBufferPos - MB_SER_PDU_PDU_OFF - MB_SER_PDU_SIZE_CRC );

        // Верните начало PDU Modbus вызывающему абоненту.
        *pucFrame = ( uint8_t * ) & ucRTUBuf[MB_SER_PDU_PDU_OFF];
    }
    else
    {  eStatus = MB_EIO;  }

    sei();
    return eStatus;
}

eMBErrorCode  eMBRTUSend( uint8_t ucSlaveAddress, const uint8_t * pucFrame, uint16_t  usLength )
{
    uint16_t          usCRC16;

    cli(); 

    // Проверьте, находится ли приемник все еще в режиме ожидания. 
	// В противном случае мы замедлили бы обработку полученного кадра, 
	// и мастер отправил бы другой кадр по сети. 
	// Мы должны прервать отправку фрейма.
    if( eRcvState == STATE_RX_IDLE )
    {
        // Первый байт перед Modbus-PDU - это адрес ведомого устройства.
        pucSndBufferCur = ( uint8_t * ) pucFrame - 1;
        usSndBufferCount = 1;

        // Теперь скопируйте Modbus-PDU в Modbus-Serial-Line-PDU.
        pucSndBufferCur[MB_SER_PDU_ADDR_OFF] = ucSlaveAddress;
        usSndBufferCount += usLength;

        /* Calculate CRC16 checksum for Modbus-Serial-Line-PDU. */
        usCRC16 = usMBCRC16( ( uint8_t * ) pucSndBufferCur, usSndBufferCount );
        ucRTUBuf[usSndBufferCount++] = ( uint8_t )( usCRC16 & 0xFF );
        ucRTUBuf[usSndBufferCount++] = ( uint8_t )( usCRC16 >> 8 );

        /* Activate the transmitter. */
        eSndState = STATE_TX_XMIT; // включить статус передачи пакета,  сброс этого статуса будет - когда закончиться передача этого пакета
        vMBPortSerialEnable( false, true );
    }

    sei();
    return MB_ENOERR;
}

void  xMBRTUReceiveFSM( void )
{
    uint8_t           ucByte;

    /* Always read the int8_tacter. постоянно читать символ*/
    //( void )xMBPortSerialGetByte( ( int8_t * ) & ucByte );
	ucByte = UDR0;
	
    switch ( eRcvState )
    {
        /* If we have received a int8_tacter in the init state we have to
         * wait until the frame is finished.
         если получили статус init, ждем пока закончиться фрейм*/
    case STATE_RX_INIT:
        vMBPortTimersEnable(  );
        break;

        /* In the error state we wait until all int8_tacters in the
         * damaged frame are transmitted.
         */
    case STATE_RX_ERROR:
        vMBPortTimersEnable(  );
        break;

        /* In the idle state we wait for a new int8_tacter. If a int8_tacter
         * is received the t1.5 and t3.5 timers are started and the
         * receiver is in the state STATE_RX_RECEIVCE.
         */
    case STATE_RX_IDLE:
        usRcvBufferPos = 0;
        ucRTUBuf[usRcvBufferPos++] = ucByte;
        eRcvState = STATE_RX_RCV;

        /* Enable t3.5 timers. */
        vMBPortTimersEnable(  );
        break;

        /* We are currently receiving a frame. Reset the timer after
         * every int8_tacter received. If more than the maximum possible
         * number of bytes in a modbus frame is received the frame is
         * ignored.
         */
    case STATE_RX_RCV:
        if( usRcvBufferPos < MB_SER_PDU_SIZE_MAX )
			{  ucRTUBuf[usRcvBufferPos++] = ucByte;  }
        else
			{ eRcvState = STATE_RX_ERROR; }
        vMBPortTimersEnable(  );
        break;
    }
//    return xTaskNeedSwitch;
}

void xMBRTUTransmitFSM( void ) // обработчик прерывания - БАЙТ ПЕРЕДАН
{
 //   bool            xNeedPoll = FALSE;

    switch ( eSndState )
    {
    case STATE_TX_IDLE: // Мы не должны получать событие передатчика, если передатчик находится в состоянии ожидания.
        vMBPortSerialEnable( true, false ); // отключаем передатчик, включаем прием
        break;

    case STATE_TX_XMIT:
        if( usSndBufferCount != 0 ) // проверить, закончилась ли передача всего пакета
        {
			UDR0 = ( char )*pucSndBufferCur ; // засунуть в буфер передачи следующий байт
            pucSndBufferCur++;  /* next byte in sendbuffer. */
            usSndBufferCount--;
        }
        else
        {
			xMBPortEventPost( EV_FRAME_SENT );   // пишем событие - передача окончена
            vMBPortSerialEnable( true, false ); // если пакет закончен,  отключаем передатчик, включаем прием
            eSndState = STATE_TX_IDLE;
        }
        break;
    }
  //  return xNeedPoll;
}

void xMBRTUTimerT35Expired( void )
{
 //   bool            xNeedPoll = FALSE;

    switch ( eRcvState )
    {
        /* Timer t35 expired. Startup phase is finished. */
    case STATE_RX_INIT:
        //xNeedPoll = 
		xMBPortEventPost( EV_READY );
        break;

        /* A frame was received and t35 expired. Notify the listener that
         * a new frame was received. */
    case STATE_RX_RCV:
        //xNeedPoll = 
		xMBPortEventPost( EV_FRAME_RECEIVED );
        break;

        /* An error occured while receiving the frame. */
    case STATE_RX_ERROR:
        break;
    }

    // vMBPortTimersDisable(  );
		    TCCR1B &= ~((1<< CS12) | (1<< CS10));// Disable the timer.
		    TIMSK1 &= ~(1<< OCIE1A);// Disable the output compare interrupts for channel A/B.
		    TIFR1 |= (1<< OCF1A ) ;// Clear output compare flags for channel A/B.
    eRcvState = STATE_RX_IDLE;

  //  return xNeedPoll;
}
