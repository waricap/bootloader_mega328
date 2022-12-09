/*
 * main.h
 *
 *
 * Created: 15.02.2022 14:35:53
 *  Author: user
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define F_CPU 16000000UL // ќбъ€вление частоты микроконтроллера дл€ макросов _delay_us
#define MB_TIMER_PRESCALER      ( 1024UL )
#define MB_TIMER_TICKS          ( F_CPU / MB_TIMER_PRESCALER )
#define MB_50US_TICKS           ( 20000UL )

#include "avr/io.h"
#include "avr/wdt.h"
#include "util/delay.h"
#include <stdbool.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/boot.h>

/* ----------------------- Modbus includes ----------------------------------*/
#include "modbus/mb.h"
#include "modbus/mbrtu.h"
#include "modbus/mbport.h"
#include "modbus/mbutils.h"


#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif



/* ----------------------- Defines ------------------------------------------*/
#define REG_HOLDING_START 0
#define REG_HOLDING_NREGS 132

/* ----------------------- Defines ------------------------------------------*/
#define MB_PDU_FUNC_READ_ADDR_OFF               ( MB_PDU_DATA_OFF + 0)
#define MB_PDU_FUNC_READ_REGCNT_OFF             ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READ_SIZE                   ( 4 )
#define MB_PDU_FUNC_READ_REGCNT_MAX             ( 0x007D )

#define MB_PDU_FUNC_WRITE_ADDR_OFF              ( MB_PDU_DATA_OFF + 0)
#define MB_PDU_FUNC_WRITE_VALUE_OFF             ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_WRITE_SIZE                  ( 4 )

#define MB_PDU_FUNC_WRITE_MUL_ADDR_OFF          ( MB_PDU_DATA_OFF + 0 )
#define MB_PDU_FUNC_WRITE_MUL_REGCNT_OFF        ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_WRITE_MUL_BYTECNT_OFF       ( MB_PDU_DATA_OFF + 4 )
#define MB_PDU_FUNC_WRITE_MUL_VALUES_OFF        ( MB_PDU_DATA_OFF + 5 )
#define MB_PDU_FUNC_WRITE_MUL_SIZE_MIN          ( 5 )
#define MB_PDU_FUNC_WRITE_MUL_REGCNT_MAX        ( 0x0078 )

#define MB_PDU_FUNC_READWRITE_READ_ADDR_OFF     ( MB_PDU_DATA_OFF + 0 )
#define MB_PDU_FUNC_READWRITE_READ_REGCNT_OFF   ( MB_PDU_DATA_OFF + 2 )
#define MB_PDU_FUNC_READWRITE_WRITE_ADDR_OFF    ( MB_PDU_DATA_OFF + 4 )
#define MB_PDU_FUNC_READWRITE_WRITE_REGCNT_OFF  ( MB_PDU_DATA_OFF + 6 )
#define MB_PDU_FUNC_READWRITE_BYTECNT_OFF       ( MB_PDU_DATA_OFF + 8 )
#define MB_PDU_FUNC_READWRITE_WRITE_VALUES_OFF  ( MB_PDU_DATA_OFF + 9 )
#define MB_PDU_FUNC_READWRITE_SIZE_MIN          ( 9 )
/* ----------------------- Defines ------------------------------------------*/
#define MB_PDU_SIZE_MAX     253 /*!< Maximum size of a PDU. */
#define MB_PDU_SIZE_MIN     1   /*!< Function Code */
#define MB_PDU_FUNC_OFF     0   /*!< Offset of function code in PDU. */
#define MB_PDU_DATA_OFF     1   /*!< Offset for response data in PDU. */


//static uint16_t	usReg_HOLDING_Start		= REG_HOLDING_START;

uint16_t		usReg_HOLDING_Buf[REG_HOLDING_NREGS];




bool input_button_US;		// pin18 => PB4 => нажата кнопка ==0, отпущена ==1 (подвес +5)	==> будет работать функци€ перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].1 ==>	LW101i1_btn_us		перекидос

//bool input_button_TEN;		// pin19 => PB5 => нажата кнопка ==0, отпущена ==1	(подвес +5)	==> будет работать функци€ перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].2 ==>	LW101i2_btn_ten		перекидос

char count_PB4; // => pin18


#endif /* MAIN_H_ */