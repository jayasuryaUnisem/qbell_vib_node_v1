#ifndef MAIN_H
#define MAIN_H

#include "BC66F3652.h"
#include "hal_i2c.h"
#include "hal_ktd.h"
#include "hal_adc.h"
#include "hal_uart.h"
#include "hal_gpio.h"
#include "hal_rf.h"

#define WDTC()                                  (_wdtc=0xa8)
#define NULL()									'\0'

//typedef unsigned char u8;
//typedef unsigned short u16;

extern void delay(unsigned short);


typedef struct int_flags
{
    unsigned char int0_isr_flag;
    unsigned char int1_isr_flag;
    unsigned char vibMotor;
}int_flags;

//struct define_flag Mflag;


#endif