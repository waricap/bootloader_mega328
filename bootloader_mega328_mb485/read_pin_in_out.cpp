/*
 * read_pin_in_out.cpp
 *
 *
 * Created: 18.03.2022 11:24:03
 *  Author: durov_av
 */ 
/*
bool status_pin_ten;	// PC5 =>	pin28
bool status_pin_us;		// PC4 =>	pin27
bool status_pin_us2_out1;	// PD5 =>	pin11
bool status_pin_us3_out2;	// PD2 =>	pin4
bool status_pin_vent_out3;	// PC2 =>	pin25
bool status_pin_out4;	// PB2 =>	pin16
bool status_pin_fs_out5;	// PB1 =>	pin15

bool input_IN_main_plata;	// pin24 => PC1 => c учетом LW202.8_mode_DatLevel == usReg_HOLDING_Buf[3].8	типа датч уровня будет формироваться ==>  input_DU ==>  ==1 есть вода,  ==0 нет
bool input_button_US;		// pin18 => PB4 => нажата кнопка ==0, отпущена ==1 (подвес +5)	==> будет работать функция перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].1 ==>	LW101i1_btn_us		перекидос
bool input_button_TEN;		// pin19 => PB5 => нажата кнопка ==0, отпущена ==1	(подвес +5)	==> будет работать функция перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].2 ==>	LW101i2_btn_ten		перекидос
bool input_IN1_adv_plata;	// pin6  => PD4 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].3 ==>	LW101i3_di1_adv		==1 подано +24в,   ==0 нет
bool input_IN2_adv_plata;	// pin5  => PD3 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].4 ==>	LW101i4_di2_adv		==1 подано +24в,   ==0 нет
bool input_IN3_adv_plata;	// pin14 => PB0 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].5 ==>	LW101i5_di3_adv		==1 подано +24в,   ==0 нет
bool input_IN4_adv_plata;	// pin13 => PD7 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].6 ==>	LW101i6_di4_adv		==1 подано +24в,   ==0 нет
bool input_IN5_adv_plata;	// pin12 => PD6


int8_t count_PC5; // =>	pin28
int8_t count_PC4; // =>	pin27
int8_t count_PD5; // =>	pin11
int8_t count_PD2; // =>	pin4
int8_t count_PC2; // =>	pin25
int8_t count_PB2; // =>	pin16
int8_t count_PB1; // =>	pin15

int8_t count_PC1; // => pin24
int8_t count_PB4; // => pin18
int8_t count_PB5; // => pin19
int8_t count_PD4; // => pin6
int8_t count_PD3; // => pin5
int8_t count_PB0; // => pin14
int8_t count_PD7; // => pin13
int8_t count_PD6; // => pin12
*/

#include "avr/io.h"

extern bool input_button_US;		// pin18 => PB4 => нажата кнопка ==0, отпущена ==1 (подвес +5)	==> будет работать функция перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].1 ==>	LW101i1_btn_us		перекидос
extern bool input_button_TEN;		// pin19 => PB5 => нажата кнопка ==0, отпущена ==1	(подвес +5)	==> будет работать функция перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].2 ==>	LW101i2_btn_ten		перекидос


extern int8_t count_PB4; // => pin18
extern int8_t count_PB5; // => pin19


void read_pin_in_out(void)
{
	// ===============	input_button_US;		// pin18 => PB4 => нажата кнопка ==0, отпущена ==1 (подвес +5)
	if ((PINB & (1 << 4)) > 0)
	{
		count_PB4-- ;
		if (count_PB4 <-5) {count_PB4 =-5; input_button_US = true ; }
	}
	else
	{
		count_PB4++ ;
		if (count_PB4 > 5) {count_PB4 = 5; input_button_US = false ; }
	}

	// ===============	bool input_button_TEN;		// pin19 => PB5 => нажата кнопка ==0, отпущена ==1	(подвес +5)
	if ((PINB & (1 << 5)) > 0)
	{
		count_PB5-- ;
		if (count_PB5 <-5) {count_PB5 =-5; input_button_TEN = true ; }
	}
	else
	{
		count_PB5++ ;
		if (count_PB5 > 5) {count_PB5 = 5; input_button_TEN = false ; }
	}

	

	return;
}