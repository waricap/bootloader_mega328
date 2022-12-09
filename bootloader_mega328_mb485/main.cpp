/*
 * mb485_16_mega328_US.cpp
 *
 *
 * Created: 17.03.2022 7:23:14
 * Author : durov_av
 
				 LW200_termo_set	==> usReg_HOLDING_Buf[1]	==> setup_termo_gradus
				 LW201_termo_max_us ==> usReg_HOLDING_Buf[2]	==> setup_termo_max_us
				 LW202_cmd__xx__	==> usReg_HOLDING_Buf[3]	==> �������� ������� �� �����
				 LW203_Upower_td	==> usReg_HOLDING_Buf[4]	==> ���������� ������� +5� �� ������������ 
				 LW204_Uaref_td		==> usReg_HOLDING_Buf[5]	==> ���������� Aref   +5=2kom=Aref=2kom=GND   ��� ������������
				 LW205_Rtd5v		==> usReg_HOLDING_Buf[6]	==> ������������� (2���), �������� �� ��   +5  �� ������������
				 
				 termo_curr_x10			==> usRegInputBuf[1]	=> LW100_termo_current_x10  +10
				 infa_discret ._x_		==> usRegInputBuf[2]	=> LW101.x
				 info_OUT_onoff ._x_	==> usRegInputBuf[3]	=> LW102.x
				 motochas_mm_US			==> usRegInputBuf[4]	==>LW103
				 motochas_hh_US			==> usRegInputBuf[5]	==>LW104
				 motochas_mm_TEN		==> usRegInputBuf[6]	==>LW105
				 motochas_hh_TEN		==> usRegInputBuf[7]	==>LW106
				 motochas_mm_FS			==> usRegInputBuf[8]	==>LW107
				 motochas_hh_FS			==> usRegInputBuf[9]	==>LW108
				 
				 // ================== CMD ===================== //cmd_vent_out3
				 LW202.0_cmd_nagrev		==>	usReg_HOLDING_Buf[3].0 ==>	PC5 =>	pin28 => status_pin_ten	=>	LED-HEAT =>		����� �EN-triac		==>	info_ten	==>	usRegInputBuf[3].0 ==>	LW102i0_info_onoff_ten		
				 LW202.1_cmd_nagrev2	==>	usReg_HOLDING_Buf[3].1 ==>
				 LW202.2_cmd_us			==>	usReg_HOLDING_Buf[3].2 ==>	PC4 =>	pin27 => status_pin_us		=>	LED-SONIC =>	����� OK TIMER ==>	info_us		==>	usRegInputBuf[3].2 ==>	LW102i2_infa_us
				 LW202.3_cmd_us2_out1	==>	usReg_HOLDING_Buf[3].3 ==>	PD5 =>	pin11 => status_pin_us2_out1 =>	�����_���� =>	�����_ OUT1 ==>		info_out1	==>	usRegInputBuf[3].3 ==>	LW102i3_infa_onoff_out1
				 LW202.4_cmd_us3_out2	==>	usReg_HOLDING_Buf[3].4 ==>	PD2 =>	pin4  => status_pin_us3_out2 =>	�����_���� =>	�����_ OUT2 ==>		info_out2	==>	usRegInputBuf[3].4 ==>	LW102i4_infa_onoff_out2
				 LW202.5_cmd_out4		==>	usReg_HOLDING_Buf[3].5 ==>	PB2 =>	pin16 => status_pin_out4	=>	�����_���� =>	�����_ OUT4 ==>		info_out4	==>	usRegInputBuf[3].5 ==>	LW102i5_infa_onoff_out4
				 LW202.6_cmd_fs_out5	==>	usReg_HOLDING_Buf[3].6 ==>	PB1 =>	pin15 => status_pin_fs_out5 =>	�����_���� =>	�����_ OUT5 ==>		info_out5	==>	usRegInputBuf[3].6 ==>	LW102i6_infa_onoff_out5
				 LW202.7_cmd_vent_out3  ==>	usReg_HOLDING_Buf[3].7 ==>	PC2 =>	pin25 => status_pin_vent_out3=>	�����_���� =>	�����_ OUT3 ==>		info_out3	==>	usRegInputBuf[3].7 ==>	LW102i7_infa_onoff_out3
				 LW202.8_mode_termodat	==>	usReg_HOLDING_Buf[3].8 ==>  ==0 ����������� NTC_10kOm,    ==1 ����������� Pt1000
				 LW202.9_mode_DatLevel	==>	usReg_HOLDING_Buf[3].9 ==>  ==0 ������ �� +24�,    ==1 ������ ������ ����������� OK-NPN
				 LW202.F_modbus			==>	usReg_HOLDING_Buf[3].F ==>		=== modbus_on_off ===																==>	usRegInputBuf[3].F ==>	LW102iF_modbus_onoff
				 
				 // ================ Input ===================== //
				 input_IN_main_plata ==>	pin24 => PC1 => ���������� ������� ������ ==0, ������� ==1	==> ��� ���� ������ ������-���������-������-�����, ������ ���� 1�1 ==>	input_DU ==>  usRegInputBuf[2].0 ==>	LW101i0_du		==1 ���� ����,  ==0 ���
				 input_IN1_adv_plata ==>	pin6  => PD4 => ���������� ������� ������ ==0, ������� ==1	==> ������ +24�, ������ ��������, ������ �������� ����� ����������.==>	usRegInputBuf[2].1 ==>	LW101i1_di1_adv		==1 ������ +24�,   ==0 ���
				 input_IN2_adv_plata ==>	pin5  => PD3 => ���������� ������� ������ ==0, ������� ==1	==> ������ +24�, ������ ��������, ������ �������� ����� ����������.==>	usRegInputBuf[2].2 ==>	LW101i2_di2_adv		==1 ������ +24�,   ==0 ���
				 input_IN3_adv_plata ==>	pin14 => PB0 => ���������� ������� ������ ==0, ������� ==1	==> ������ +24�, ������ ��������, ������ �������� ����� ����������.==>	usRegInputBuf[2].3 ==>	LW101i3_di3_adv		==1 ������ +24�,   ==0 ���
				 input_button_US	 ==>	pin18 => PB4 => ������ ������ ==0, �������� ==1 (������ +5)	==> ����� �������� ������� ���������� �� ���������� ������		   ==>	usRegInputBuf[2].4 ==>	LW101i4_btn_us		���������
				 input_button_TEN	 ==>	pin19 => PB5 => ������ ������ ==0, �������� ==1	(������ +5)	==> ����� �������� ������� ���������� �� ���������� ������		   ==>	usRegInputBuf[2].5 ==>	LW101i5_btn_ten		���������
				 input_IN4_adv_plata ==>	pin13 => PD7 => ���������� ������� ������ ==0, ������� ==1	==> ������ +24�, ������ ��������, ������ �������� ����� ����������.==>	usRegInputBuf[2].6 ==>	LW101i6_di4_adv		==1 ������ +24�,   ==0 ���
				 input_IN5_adv_plata ==>	pin12 => PD6 => ���������� ������� ������ ==0, ������� ==1	==> ������ +24�, ������ ��������, ������ �������� ����� ����������.==>	usRegInputBuf[2].7 ==>	LW101i7_di5_adv		==1 ������ +24�,   ==0 ���
				 
*/ 

#include "main.h"


uint8_t			flag_count_press_button	= 0; // ==0xFF ������ ���� �������� ������ � �������� ����,  ==0 ��������� �����.

uint8_t			MB_adres ;
eMBErrorCode    eStatus;
bool			flag_USART_TX_vect ; // ==1 ������ ����������� ��������, ����� ���������� �������� �� �����
uint8_t    ucMBAddress;
uint16_t   usTimerOCRADelta;

uint16_t page=0;
uint8_t *buf;

uint16_t i;
uint8_t sreg; // ��������� ����������

uint16_t address;
uint16_t data;
uint16_t i_max_flash = SPM_PAGESIZE/2;
							
// -----------------------INTERRUPT ---------------------------------------- //
// -----------------------INTERRUPT ---------------------------------------- //
ISR (USART_TX_vect)  
{  PORTC &= ~( 1<< 3); } // ������� UART � ����� ������

ISR (USART_UDRE_vect)
{ xMBRTUTransmitFSM();}

ISR (USART_RX_vect)
{ xMBRTUReceiveFSM();}

ISR( TIMER1_COMPA_vect)
{ ( void )xMBRTUTimerT35Expired();}

//ISR (TIMER2_OVF_vect) /** Timer interrupt to control the sampling interval */
//{ flag_count_press_button =0xFF; } // ���� ������ ������ ���������, ��������� ����� ����� ~~16,4 ms,  ��� �� � �������� �?�

// --------------------------- fun === fun === fun === fun === fun === fun === fun ------------------------------------------------------ //
// --------------------------- fun === fun === fun === fun === fun === fun === fun ------------------------------------------------------ //
//void initTimer2() 
//{           // ������� ����� ������ �� 256, ���� 16��� ����� �������� ������������� �� 1024, COUNT_secunda ����� �������� �� 61 � main() - ��� ����� ��������� 1���.
//	TCNT2 = 0x00; // initial value
	//	TCCR2A |= (1<< COM2B0) ; //| (1<< COM2B1); //(1 << WGM21) | (1 << WGM20) |   // ������� ���� 5 - PORTD3 - OC2B ���� ����� � ��������� �� �������� ������� ������, OCR2B = pin.5 PORTD.3
//	TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22); // | (1 << WGM22) ; // frequency F_CPU/1024
//	TIMSK2 |= (1<< TOIE2);
//}

int main(void) 
{ 	
	cli();//  ����������� ����������    cli()   - ��� ����� ������ ����
	/* Enable change of Interrupt Vectors */
	MCUCR = (1<<IVCE);
	/* Move interrupts to boot Flash section */
	MCUCR = (1<<IVSEL);	
	sei();  // ������ �� ����� ����������     sei()   - ��� ����� ������ ����
	
	 // Set the Interrupt Vector Select bit,
	 // read-modify-write to preserve other configured bits
	// _PROTECTED_WRITE(CPUINT.CTRLA, (CPUINT.CTRLA | CPUINT_IVSEL_bm));
	 //Enable global interrupts

	 
		DDRB  = 0; // ����� ��������� �����,
		PORTB = 0xFF; // ������� ���� ������ � �����
		//DDRC  = 0; // ����� ��������� �����,
		//PORTC = 0xFF; // ������� ���� ������ � �����
		//DDRD  = 0; // ����� ��������� �����,
		//PORTD = 0xFF ; // ������� ���� ������ � �����

		// �o ��������� ����� ��������, ���������:
		DDRC |=(1<<3);		//	pin.26 mega328.PC3   ����� ��� �����������  MAX485
		PORTC &= ~( 1<< 3); //	pin.26 mega328.PC3     =0 -Read_max485

DDRC |=(1<<4);		//	pin.27 mega328.PC4   ����� - ����  ������
PORTC &= ~( 1<< 4);
		DDRC |=(1<<5);		//	pin.27 mega328.PC4   ����� - ����  ������
		//PORTC |= ( 1<< 5);
		
		// ========== Timer2 ����� ������� ����� 16,4 ����, ������������ ����� ��� ������� ��������� �?� � ��� ������ ��������� ��-���============= //
//		initTimer2();
//		sei();
	


		// ====== setup ModBUS ===================== setup ModBUS ========= setup ModBUS =========================================//
		ucMBAddress = 7 ;  // ����� ����� ����� � ���� ���� ��-�����
				    // ��������� UART// �������� 9600, �������������, ������ ��� �������������� ��� �� ���� PHASER
					cli();//  ����������� ����������    cli()   - ��� ����� ������ ����
				    UCSR0C|=  (1<<UCSZ01) | (1<<UCSZ00);  //  8���  ������// ����� ������ � ��� ���������  8 bit i NO variant
				    UCSR0A |= (1<<U2X0);  // ��� �����  �����������  UART
						UBRR0L=207;   // 2��������,  ���������� 9600  ��� 16 ���			
						//UBRR0L=103;   // 2��������,  ���������� 19200  ��� 16 ���
						//UBRR0L=51;		// 2��������,  ���������� 38400  ��� 16 ���
				    UBRR0H = 0;
				    UCSR0B |= (1<<RXEN0);// ��������� �����
				    UCSR0B &= ~((1<< RXEN0) | (1<< RXCIE0));
				    UCSR0B &= ~(1<< UDRE0 );
						// ��������� ������ �������
						usTimerOCRADelta = ( MB_TIMER_TICKS * 40 ) / ( MB_50US_TICKS );  // 40 = ������  ��� 9600  ���19200  ������� 16 ���
						//usTimerOCRADelta = ( MB_TIMER_TICKS * 35 ) / ( MB_50US_TICKS );  // 35 = ������  ��� 38400  ������� 16 ���
				    TCCR1A = 0x00;
				    TCCR1B = 0x00;
				    TCCR1C = 0x00;
				    TCCR1B &= ~((1<< CS12) | (1<< CS10));// Disable the timer.
				    TIMSK1 &= ~(1<< OCIE1A);// Disable the output compare interrupts for channel A/B.
				    TIFR1 |= (1<< OCF1A ) ;// Clear output compare flags for channel A/B.
			// eMBRTUStart();// Enable the Modbus Protocol Stack.
			vMBPortSerialEnable( TRUE, FALSE ); // � ��� ��� �������, ����
			vMBPortTimersEnable(  );
		sei();  // ������ �� ����� ����������     sei()   - ��� ����� ������ ����
		
		// ============ ���������� ������ ������ ���� ============================== //
		wdt_reset(); // ����� ����������� �������
		wdt_enable(WDTO_1S);// �������� ���������� ������

// ������� � ���� ������ ������������� ��������� �� ����� �� ��� ������� ��������� ���������� ������������ ����������� AVR. 
// ��� ������� ������������� ��� ������ �� ����� �������� ����-������.
// ���������� ���������� �� ����������� ������������� ��� ���� ��������.
// ��� �������� �� ���������� ������������. �������� ������ ���� ����.   
// ����� �������� ������������ ���������� ��� ��������������� ������������ ��������� ���������� ���������� �� ����� ������ ����-������.

//  ���������� == �� ��� ���������� AVR ������������ ���������. ���������� � ������������ ������ ����������, ����� ������, ������������ �� �� ��������� ����������.
//  ��� ������ �� ����������� ����� � �������: �� ����������� �������� ������� (����, ����� ATmega64/128) 
// __SPM_REGis � ������������ �����-������, ��������� � ������� ����� �������� ���������� "in" � "out" - ��������� ��������� ����� ������������ ������, 
// ��� ����� ���� ������ ������������.		


// ============================================== TEST ========================================
				for (i=0; i<64; i++) 
				{
					usReg_HOLDING_Buf[5+i] = 256*i + i;
				}
				//usReg_HOLDING_Buf[4] = 4;		// LW103
				//usReg_HOLDING_Buf[5]=517;	// LW104
				//usReg_HOLDING_Buf[6]=1019;	
				//usReg_HOLDING_Buf[7]=7;	
				// ...
				// usReg_HOLDING_Buf[67] =67;	// LW166
				 //usReg_HOLDING_Buf[68] =68;	// LW167
				 usReg_HOLDING_Buf[69] =1;	// ��� ��� 65-� �����,  ���������� ����, ����� �������� +1, � �� �������� 64 WORD == 128 BYTE




// ========== MAIN ���� ���� =========================== MAIN ���� ���� ========== MAIN ���� ���� ========== MAIN ���� ���� ==================================================//
// ========== MAIN ���� ���� =========================== MAIN ���� ���� ========== MAIN ���� ���� ========== MAIN ���� ���� ==================================================//
    while (1) 
    {
		// ====== �������� ModBUS ===================== �������� ModBUS ========= �������� ModBUS =========================================//
// TEST  TEST		if ( MB_ENOERR == eMBPoll() )
			{			
				wdt_reset();  // ����� ����������� �������, ���� ������ ������� NO �������
				usReg_HOLDING_Buf[1]++;		// LW100
				usReg_HOLDING_Buf[2]=3;		// �����  ��������, ������� ���� �������� �� ����, ���� ������� ������ ������, � ������� ����� � ����� ������� ��� ����, �� �����.
				usReg_HOLDING_Buf[3] = usReg_HOLDING_Buf[5];		// LW102
				for (i=5; i<72; i++) 
				{
					if (usReg_HOLDING_Buf[i] >0) { usReg_HOLDING_Buf[4]=i; }
				}
				// usReg_HOLDING_Buf[4] = usReg_HOLDING_Buf[6];		// LW103
				// usReg_HOLDING_Buf[5];	// LW104
				// ...
				// usReg_HOLDING_Buf[67];	// LW166
				// usReg_HOLDING_Buf[68];	// LW167
				// usReg_HOLDING_Buf[69];	// ��� ��� 65-� �����,  ���������� ����, ����� �������� +1, � �� �������� 64 WORD == 128 BYTE

				// ===============	input_button_US;		// pin18 => PB4 => ������ ������ ==0, �������� ==1 (������ +5)   if ((PINB & (1 << 4)) > 0)
				
				if ((usReg_HOLDING_Buf[69] >= 0x0FFF) | ((PINB & (1 << 4)) > 0) & (usReg_HOLDING_Buf[69] ==0)) //| (usReg_HOLDING_Buf[69] < 7))	//  usReg_HOLDING_Buf[69] ����� �������� +7, ����������, ����� ���������� ������, �������� ����� �������� ���� 255 � ��
					{ 
						boot_rww_enable ();		// ����� �������� RWW-������. ��� ��� �����, ���� �� ����� ��������� � ���������� ����� ��������.
						asm("jmp 0x0000"); // ������� � �������� ���
					}
				if (usReg_HOLDING_Buf[69] > 0)
				{
					page = (usReg_HOLDING_Buf[69]-1 + 3);	// ����� ��������, ������� ������� � ����� ���������� ������ ������
					// ============================ write boot ========================== //
					if (page == usReg_HOLDING_Buf[2])
					{
						cli();		// ��������� ����������
							boot_page_erase(page);		// ������� ������
							boot_spm_busy_wait ();      // wait, ���� ������ �� ����� ������.
							for (i=0; i<i_max_flash; i++) // SPM_PAGESIZE  128 ����  == 64 �����
							{
								address = i_max_flash*2*page + i*2;
								data	= usReg_HOLDING_Buf[i+5];
								boot_page_fill (address, data);  // ��������� ����� ��� ������,  page - ����� �������� �� flash
							}
							boot_page_write (page);	// �������� ������ �� ������ �� ����-��������.
							boot_spm_busy_wait();   // wait, ���� ������ �� ����� ��������.
						sei();						
						usReg_HOLDING_Buf[2] = page +1; // �������� ��������� ��������
						if((PORTC & (1 << 3)) == 0) // ������ ���� ���� �����, ������ �������� �����, ���� �������� - �� �����������
							{ PORTC ^= ( 1<< 4);  } // ��� �� �������� �� �������� ������ �������������� UART
						// ============================ write boot ========================== //							
					}
				}
				
			} //   if ( MB_ENOERR == eMBPoll() )
				
    } // while (1)
} // int main(void)

// ================================== ������� ������� ================================== ������� ������� ================================== ������� ������� ============= //

eMBErrorCode eMBRegHoldingCB( uint8_t * pucRegBuffer, uint16_t iRegIndex, uint16_t usNRegs, eMBRegisterMode eMode )
{
	// (  3 ) //(0x03) � ������ �������� �� ���������� ��������� ������� (Read Holding Registers).
	// (  6 ) //(0x06) � ������ ������� � ���� ������� ������� (Preset Single Register).
	//		REG_HOLDING_START 50
	//		REG_HOLDING_NREGS 16
	//		usReg_HOLDING_Start = REG_HOLDING_START;
	//		usReg_HOLDING_Buf[REG_HOLDING_NREGS];
	
			while( usNRegs > 0 )
			{
				if( eMode == MB_REG_READ) // ���� ������ - ������ ������ 4 �����: usReg_HOLDING_Buf[1] - usReg_HOLDING_Buf[4]
				{
					*pucRegBuffer++ =( uint8_t )( usReg_HOLDING_Buf[iRegIndex] >> 8 );
					*pucRegBuffer++ =( uint8_t )( usReg_HOLDING_Buf[iRegIndex] & 0x00FF );
				}
				
				if ( eMode == MB_REG_WRITE) // ���� ������ - ������ ������ ������ 128 ����: usReg_HOLDING_Buf[5] - usReg_HOLDING_Buf[132]
				{
					usReg_HOLDING_Buf[iRegIndex] = (uint16_t) * pucRegBuffer <<8;
					*pucRegBuffer++;
					usReg_HOLDING_Buf[iRegIndex] = usReg_HOLDING_Buf[iRegIndex] + (*pucRegBuffer);
					*pucRegBuffer++;
				}
				
				iRegIndex++;
				usNRegs--;
			}			

	return MB_ENOERR;
}// eMBErrorCode eMB_Reg_Holding_CB( uint8_t * pucRegBuffer, uint16_t usAddress, uint16_t usNRegs, eMBRegisterMode eMode )






