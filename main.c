#include "main.h"

extern int_flags intF;

char* a;

u16 ADC_Value;


extern struct define_flag Mflag;
//
extern _BC3602_device_ BC3602_T;

void convert_integer_to_string(char* const str, unsigned short number)
{
   
	u16 n, len = 0, i, rem;
	n = number;
	if(0 == n)
		len = 1;
	while (0 != n)
	{
		len++;
		n /= 10;	
	}
	 
	for ( i = 0; i < len; i++ )
	{
		rem = number % 10;
		number = number / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
}



void delay(unsigned short time)
{
    unsigned short a;
	unsigned char b,c;
	
    for(a=0;a<time;a++)
    {
    	for(b=0;b<5;b++)
    	{
    		for(c=0;c<102;c++) asm("nop");
    	}
    }
}

void sysInit()
{
    WDTC();
    uart_prot_init();
    delay(100);
    adc_init();
    IIC_Init();
    ktd_en();
    ktd_clear();
    delay(100);
   	int_init();
    delay(1000); 
}

void main()
{
    Sys_init();

   	sysInit();

	RF_Init();																				// RF Initialization
	RF_Parameter_loading();
//	BC3602_WriteRegister(IO2_REGS,0xcd);													// debug use
	BC3602_T.mode = RF_RX;																	// set RF mode flag as RX mode
	
	BC3602_T.mode = RF_RX;	
// //	GCC_HALT();	
//	WDTC();
	// _pa6 = 0;
	// _pac6 = 0;
	
	// _pa5 = 0;
	// _pac5 = 1;
	// _papu5 = 1;
	// _pawu5 = 1;
	
	while(1)
	{

		if(intF.vibMotor)
		{
			unsigned char i;
			for (i = 0; i < 5; i++)
			{
				if(!WAKEUP_PIN)
				{
					MOTOR_DRV_PIN = 0;
					break;
				}
				MOTOR_DRV_PIN = 1;
				delay(1000);
				if(!WAKEUP_PIN)
				{
					MOTOR_DRV_PIN = 0;
					break;
				}
				MOTOR_DRV_PIN = 0;
				delay(500);
				if(!WAKEUP_PIN)
					break;
			}
			
			intF.vibMotor = 0;
		}

		if(!WAKEUP_PIN)
		{
			// RGB_R = 1;
			// RGB_B = 1;
			// RGB_G = 1;	
			uart_printf("Button Pressed: \n");
			if(BC3602_T.mode != RF_TX)														// while not being tx mode
			{
				uart_printf("Insied the !RX_TX\n");
				Mflag.Key_Stas = 0x01;
				KEY_Process(Mflag.Key_Stas);												// while not being tx mode
			}
			
			uart_printf("Inside the Mflag key");
			Mflag.Key_Stas = 0;						
           	intF.int1_isr_flag = 0;
			delay(100);
		}
		else
		{
			RGB_R = 0;
			RGB_B = 0;
			RGB_G = 0;

		}
		
		//_halt();
		//GCC_HALT();
		if(BC3602_T.mode == RF_TX)															// while RF mode flag = TX
			SimpleFIFO_TX_Process(&BC3602_T);												// RF Simple FIFO TX porcess
		
		if(BC3602_T.mode == RF_RX)															// while RF mode flag = RX
			SimpleFIFO_RX_Process(&BC3602_T);												// RF Simple FIFO RX porcess	
		
		RF_Finished_Process(&BC3602_T);	
		delay(100);
	}
	
}



// //*********************************************//
// // name		:	TB0_proc
// //*********************************************//
void __attribute((interrupt(0x1C))) TB0_proc(void)
{
	Mflag.fs++;
	if(Mflag.fs>=10)
	{
		Mflag.fm = 1;
		Mflag.fs = 0;
	}
	Mflag.f8ms++;
	_pb6 = ~_pb6;
}

