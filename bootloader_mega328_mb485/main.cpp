/*
 * mb485_16_mega328_US.cpp
 *
 *
 * Created: 17.03.2022 7:23:14
 * Author : durov_av
 
				 LW200_termo_set	==> usReg_HOLDING_Buf[1]	==> setup_termo_gradus
				 LW201_termo_max_us ==> usReg_HOLDING_Buf[2]	==> setup_termo_max_us
				 LW202_cmd__xx__	==> usReg_HOLDING_Buf[3]	==> входящие команды от кинко
				 LW203_Upower_td	==> usReg_HOLDING_Buf[4]	==> напряжение питания +5в на термодатчике 
				 LW204_Uaref_td		==> usReg_HOLDING_Buf[5]	==> напряжение Aref   +5=2kom=Aref=2kom=GND   для термодатчика
				 LW205_Rtd5v		==> usReg_HOLDING_Buf[6]	==> сопротивление (2кОм), подвески ТД на   +5  от термодатчика
				 
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
				 LW202.0_cmd_nagrev		==>	usReg_HOLDING_Buf[3].0 ==>	PC5 =>	pin28 => status_pin_ten	=>	LED-HEAT =>		Выход ТEN-triac		==>	info_ten	==>	usRegInputBuf[3].0 ==>	LW102i0_info_onoff_ten		
				 LW202.1_cmd_nagrev2	==>	usReg_HOLDING_Buf[3].1 ==>
				 LW202.2_cmd_us			==>	usReg_HOLDING_Buf[3].2 ==>	PC4 =>	pin27 => status_pin_us		=>	LED-SONIC =>	Выход OK TIMER ==>	info_us		==>	usRegInputBuf[3].2 ==>	LW102i2_infa_us
				 LW202.3_cmd_us2_out1	==>	usReg_HOLDING_Buf[3].3 ==>	PD5 =>	pin11 => status_pin_us2_out1 =>	плата_расш =>	Выход_ OUT1 ==>		info_out1	==>	usRegInputBuf[3].3 ==>	LW102i3_infa_onoff_out1
				 LW202.4_cmd_us3_out2	==>	usReg_HOLDING_Buf[3].4 ==>	PD2 =>	pin4  => status_pin_us3_out2 =>	плата_расш =>	Выход_ OUT2 ==>		info_out2	==>	usRegInputBuf[3].4 ==>	LW102i4_infa_onoff_out2
				 LW202.5_cmd_out4		==>	usReg_HOLDING_Buf[3].5 ==>	PB2 =>	pin16 => status_pin_out4	=>	плата_расш =>	Выход_ OUT4 ==>		info_out4	==>	usRegInputBuf[3].5 ==>	LW102i5_infa_onoff_out4
				 LW202.6_cmd_fs_out5	==>	usReg_HOLDING_Buf[3].6 ==>	PB1 =>	pin15 => status_pin_fs_out5 =>	плата_расш =>	Выход_ OUT5 ==>		info_out5	==>	usRegInputBuf[3].6 ==>	LW102i6_infa_onoff_out5
				 LW202.7_cmd_vent_out3  ==>	usReg_HOLDING_Buf[3].7 ==>	PC2 =>	pin25 => status_pin_vent_out3=>	плата_расш =>	Выход_ OUT3 ==>		info_out3	==>	usRegInputBuf[3].7 ==>	LW102i7_infa_onoff_out3
				 LW202.8_mode_termodat	==>	usReg_HOLDING_Buf[3].8 ==>  ==0 термодатчик NTC_10kOm,    ==1 термодатчик Pt1000
				 LW202.9_mode_DatLevel	==>	usReg_HOLDING_Buf[3].9 ==>  ==0 геркон на +24в,    ==1 датчик уровня термический OK-NPN
				 LW202.F_modbus			==>	usReg_HOLDING_Buf[3].F ==>		=== modbus_on_off ===																==>	usRegInputBuf[3].F ==>	LW102iF_modbus_onoff
				 
				 // ================ Input ===================== //
				 input_IN_main_plata ==>	pin24 => PC1 => зажигается входной оптрон ==0, погашен ==1	==> нет воды геркон опущен-закорочен-оптрон-горит, сигнал идет 1к1 ==>	input_DU ==>  usRegInputBuf[2].0 ==>	LW101i0_du		==1 есть вода,  ==0 нет
				 input_IN1_adv_plata ==>	pin6  => PD4 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].1 ==>	LW101i1_di1_adv		==1 подано +24в,   ==0 нет
				 input_IN2_adv_plata ==>	pin5  => PD3 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].2 ==>	LW101i2_di2_adv		==1 подано +24в,   ==0 нет
				 input_IN3_adv_plata ==>	pin14 => PB0 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].3 ==>	LW101i3_di3_adv		==1 подано +24в,   ==0 нет
				 input_button_US	 ==>	pin18 => PB4 => нажата кнопка ==0, отпущена ==1 (подвес +5)	==> будет работать функция перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].4 ==>	LW101i4_btn_us		перекидос
				 input_button_TEN	 ==>	pin19 => PB5 => нажата кнопка ==0, отпущена ==1	(подвес +5)	==> будет работать функция перекидоса по отпусканию кнопки		   ==>	usRegInputBuf[2].5 ==>	LW101i5_btn_ten		перекидос
				 input_IN4_adv_plata ==>	pin13 => PD7 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].6 ==>	LW101i6_di4_adv		==1 подано +24в,   ==0 нет
				 input_IN5_adv_plata ==>	pin12 => PD6 => зажигается входной оптрон ==0, погашен ==1	==> подано +24в, оптрон зажжется, сигнал дискрета будет инвертиров.==>	usRegInputBuf[2].7 ==>	LW101i7_di5_adv		==1 подано +24в,   ==0 нет
				 
*/ 

#include "main.h"


uint8_t			flag_count_press_button	= 0; // ==0xFF значит надо опросить кнопки и сбросить флаг,  ==0 прокинуть опрос.

uint8_t			MB_adres ;
eMBErrorCode    eStatus;
bool			flag_USART_TX_vect ; // ==1 значит закончилась передача, можно переводить приемник на прием
uint8_t    ucMBAddress;
uint16_t   usTimerOCRADelta;

uint16_t page=0;
uint8_t *buf;

uint16_t i;
uint8_t sreg; // сохранить прерывания

uint16_t address;
uint16_t data;
uint16_t i_max_flash = SPM_PAGESIZE/2;
							
// -----------------------INTERRUPT ---------------------------------------- //
// -----------------------INTERRUPT ---------------------------------------- //
ISR (USART_TX_vect)  
{  PORTC &= ~( 1<< 3); } // перевод UART в режим приема

ISR (USART_UDRE_vect)
{ xMBRTUTransmitFSM();}

ISR (USART_RX_vect)
{ xMBRTUReceiveFSM();}

ISR( TIMER1_COMPA_vect)
{ ( void )xMBRTUTimerT35Expired();}

//ISR (TIMER2_OVF_vect) /** Timer interrupt to control the sampling interval */
//{ flag_count_press_button =0xFF; } // флаг опроса кнопок поднимаем, получитьс¤ опрос через ~~16,4 ms,  там же и стартует ј?ѕ

// --------------------------- fun === fun === fun === fun === fun === fun === fun ------------------------------------------------------ //
// --------------------------- fun === fun === fun === fun === fun === fun === fun ------------------------------------------------------ //
//void initTimer2() 
//{           // счЄтчик будет тикать до 256, такт 16Мгц будет делиться предделителем на 1024, COUNT_secunda будет делиться на 61 в main() - это будет считаться 1сек.
//	TCNT2 = 0x00; // initial value
	//	TCCR2A |= (1<< COM2B0) ; //| (1<< COM2B1); //(1 << WGM21) | (1 << WGM20) |   // перекид ноги 5 - PORTD3 - OC2B этот вывод ¤ подключал дл¤ проверки частоты кварца, OCR2B = pin.5 PORTD.3
//	TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22); // | (1 << WGM22) ; // frequency F_CPU/1024
//	TIMSK2 |= (1<< TOIE2);
//}

int main(void) 
{ 	
	cli();//  заблокируем прерывания    cli()   - там такой дефайн есть
	/* Enable change of Interrupt Vectors */
	MCUCR = (1<<IVCE);
	/* Move interrupts to boot Flash section */
	MCUCR = (1<<IVSEL);	
	sei();  // вернем на место прерывания     sei()   - там такой дефайн есть
	
	 // Set the Interrupt Vector Select bit,
	 // read-modify-write to preserve other configured bits
	// _PROTECTED_WRITE(CPUINT.CTRLA, (CPUINT.CTRLA | CPUINT_IVSEL_bm));
	 //Enable global interrupts

	 
		DDRB  = 0; // везде назначаем входа,
		PORTB = 0xFF; // подт¤жка всех входов к плюсу
		//DDRC  = 0; // везде назначаем входа,
		//PORTC = 0xFF; // подт¤жка всех входов к плюсу
		//DDRD  = 0; // везде назначаем входа,
		//PORTD = 0xFF ; // подт¤жка всех входов к плюсу

		// нo некоторые будут выходами, назначаем:
		DDRC |=(1<<3);		//	pin.26 mega328.PC3   выход для переключени¤  MAX485
		PORTC &= ~( 1<< 3); //	pin.26 mega328.PC3     =0 -Read_max485

DDRC |=(1<<4);		//	pin.27 mega328.PC4   выход - тест  старта
PORTC &= ~( 1<< 4);
		DDRC |=(1<<5);		//	pin.27 mega328.PC4   выход - тест  старта
		//PORTC |= ( 1<< 5);
		
		// ========== Timer2 будет долбить такты 16,4 мсек, использовать будем для запуска измерений ј?ѕ и для опроса клавиатур ”«-“ЁЌ============= //
//		initTimer2();
//		sei();
	


		// ====== setup ModBUS ===================== setup ModBUS ========= setup ModBUS =========================================//
		ucMBAddress = 7 ;  // такой адрес будет у всех плат УЗ-ванна
				    // настроить UART// скорость 9600, исключительно, потому что предполагается ещё на шине PHASER
					cli();//  заблокируем прерывания    cli()   - там такой дефайн есть
				    UCSR0C|=  (1<<UCSZ01) | (1<<UCSZ00);  //  8бит  данных// длина данных и без вариантов  8 bit i NO variant
				    UCSR0A |= (1<<U2X0);  // это будет  асинхронный  UART
						UBRR0L=207;   // 2значения,  определяют 9600  при 16 МГц			
						//UBRR0L=103;   // 2значения,  определяют 19200  при 16 МГц
						//UBRR0L=51;		// 2значения,  определяют 38400  при 16 МГц
				    UBRR0H = 0;
				    UCSR0B |= (1<<RXEN0);// разрешаем прием
				    UCSR0B &= ~((1<< RXEN0) | (1<< RXCIE0));
				    UCSR0B &= ~(1<< UDRE0 );
						// настроить таймер модбуса
						usTimerOCRADelta = ( MB_TIMER_TICKS * 40 ) / ( MB_50US_TICKS );  // 40 = таймер  при 9600  при19200  частота 16 МГц
						//usTimerOCRADelta = ( MB_TIMER_TICKS * 35 ) / ( MB_50US_TICKS );  // 35 = таймер  при 38400  частота 16 МГц
				    TCCR1A = 0x00;
				    TCCR1B = 0x00;
				    TCCR1C = 0x00;
				    TCCR1B &= ~((1<< CS12) | (1<< CS10));// Disable the timer.
				    TIMSK1 &= ~(1<< OCIE1A);// Disable the output compare interrupts for channel A/B.
				    TIFR1 |= (1<< OCF1A ) ;// Clear output compare flags for channel A/B.
			// eMBRTUStart();// Enable the Modbus Protocol Stack.
			vMBPortSerialEnable( TRUE, FALSE ); // и так уже сделано, выше
			vMBPortTimersEnable(  );
		sei();  // вернем на место прерывания     sei()   - там такой дефайн есть
		
		// ============ сторожевой таймер должен быть ============================== //
		wdt_reset(); // сброс сторожевого таймера
		wdt_enable(WDTO_1S);// включаем сторожевой таймер

// Макросы в этом модуле предоставляют интерфейс на языке Си для функций поддержки загрузчика определенных процессоров AVR. 
// Эти макросы предназначены для работы со всеми объемами флэш-памяти.
// Глобальные прерывания не отключаются автоматически для этих макросов.
// Это остается на усмотрение программиста. Смотрите пример кода ниже.   
// Также смотрите спецификацию процессора для предостережений относительно включения глобальных прерываний во время записи флэш-памяти.

//  примечание == Не все процессоры AVR поддерживают загрузчик. Обратитесь к спецификации вашего процессора, чтобы узнать, обеспечивает ли он поддержку загрузчика.
//  что делать по электронной почте с Мареком: На устройствах меньшего размера (всех, кроме ATmega64/128) 
// __SPM_REGis в пространстве ввода-вывода, доступном с помощью более коротких инструкций "in" и "out" - поскольку загрузчик имеет ограниченный размер, 
// это может быть важной оптимизацией.		


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
				 usReg_HOLDING_Buf[69] =1;	// это уже 65-е слово,  передается инфа, номер страницы +1, а на странице 64 WORD == 128 BYTE




// ========== MAIN цикл цикл =========================== MAIN цикл цикл ========== MAIN цикл цикл ========== MAIN цикл цикл ==================================================//
// ========== MAIN цикл цикл =========================== MAIN цикл цикл ========== MAIN цикл цикл ========== MAIN цикл цикл ==================================================//
    while (1) 
    {
		// ====== проверим ModBUS ===================== проверим ModBUS ========= проверим ModBUS =========================================//
// TEST  TEST		if ( MB_ENOERR == eMBPoll() )
			{			
				wdt_reset();  // сброс сторожевого таймера, если запрос модбуса NO ошибкой
				usReg_HOLDING_Buf[1]++;		// LW100
				usReg_HOLDING_Buf[2]=3;		// номер  страница, которую надо записать во флеш, этот регистр читает мастер, и поэтому знает и потом пришлет что надо, но потом.
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
				// usReg_HOLDING_Buf[69];	// это уже 65-е слово,  передается инфа, номер страницы +1, а на странице 64 WORD == 128 BYTE

				// ===============	input_button_US;		// pin18 => PB4 => нажата кнопка ==0, отпущена ==1 (подвес +5)   if ((PINB & (1 << 4)) > 0)
				
				if ((usReg_HOLDING_Buf[69] >= 0x0FFF) | ((PINB & (1 << 4)) > 0) & (usReg_HOLDING_Buf[69] ==0)) //| (usReg_HOLDING_Buf[69] < 7))	//  usReg_HOLDING_Buf[69] номер страницы +7, Передатчик, когда закончатся данные, поднимет номер страницы выше 255 и ОК
					{ 
						boot_rww_enable ();		// Снова включите RWW-раздел. Нам это нужно, если мы хотим вернуться к приложению после загрузки.
						asm("jmp 0x0000"); // переход к основной прг
					}
				if (usReg_HOLDING_Buf[69] > 0)
				{
					page = (usReg_HOLDING_Buf[69]-1 + 3);	// номер страницы, который записан в конце пришедшего пекета данных
					// ============================ write boot ========================== //
					if (page == usReg_HOLDING_Buf[2])
					{
						cli();		// отключаем прерывания
							boot_page_erase(page);		// стереть память
							boot_spm_busy_wait ();      // wait, пока память не будет стерта.
							for (i=0; i<i_max_flash; i++) // SPM_PAGESIZE  128 байт  == 64 слова
							{
								address = i_max_flash*2*page + i*2;
								data	= usReg_HOLDING_Buf[i+5];
								boot_page_fill (address, data);  // заполняем буфер для записи,  page - номер страницы во flash
							}
							boot_page_write (page);	// записать данные из буфера на флэш-страницу.
							boot_spm_busy_wait();   // wait, пока память не будет записана.
						sei();						
						usReg_HOLDING_Buf[2] = page +1; // запросим следующую страницу
						if((PORTC & (1 << 3)) == 0) // только если идет прием, меняем значение порта, если передача - то прокидываем
							{ PORTC ^= ( 1<< 4);  } // что бы случайно не помешать работе приемапередачи UART
						// ============================ write boot ========================== //							
					}
				}
				
			} //   if ( MB_ENOERR == eMBPoll() )
				
    } // while (1)
} // int main(void)

// ================================== функции модбуса ================================== функции модбуса ================================== функции модбуса ============= //

eMBErrorCode eMBRegHoldingCB( uint8_t * pucRegBuffer, uint16_t iRegIndex, uint16_t usNRegs, eMBRegisterMode eMode )
{
	// (  3 ) //(0x03) Ч чтение значений из нескольких регистров хранени¤ (Read Holding Registers).
	// (  6 ) //(0x06) Ч запись значени¤ в один регистр хранени¤ (Preset Single Register).
	//		REG_HOLDING_START 50
	//		REG_HOLDING_NREGS 16
	//		usReg_HOLDING_Start = REG_HOLDING_START;
	//		usReg_HOLDING_Buf[REG_HOLDING_NREGS];
	
			while( usNRegs > 0 )
			{
				if( eMode == MB_REG_READ) // если чтение - читать только 4 слова: usReg_HOLDING_Buf[1] - usReg_HOLDING_Buf[4]
				{
					*pucRegBuffer++ =( uint8_t )( usReg_HOLDING_Buf[iRegIndex] >> 8 );
					*pucRegBuffer++ =( uint8_t )( usReg_HOLDING_Buf[iRegIndex] & 0x00FF );
				}
				
				if ( eMode == MB_REG_WRITE) // если запись - писать всегда только 128 слов: usReg_HOLDING_Buf[5] - usReg_HOLDING_Buf[132]
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






