#ifndef HAL_RF_H
#define HAL_RF_H
#include "main.h"

// typedef unsigned char u8;
// typedef unsigned short u16;

#include "RF_API.h"
#include "SYS_API.h"
#include "Configuration.h"


extern void Sys_init(void);
extern void fun_RamInit();
extern void KEY_Process(unsigned char key_status);
extern void RF_Finished_Process(_BC3602_device_ *BC3602_T);
extern void DATA_Process(unsigned char *FIFO);
extern void RF_Process(void);
extern void RF_Process_Inint(void);
extern void System_deepsleep(void);


struct define_flag
{
    unsigned char Key_Stas;
    unsigned char LED_Stas;
    unsigned char fRFINT:1;
    unsigned char f8ms:1;
    unsigned char fs;
    unsigned char fm; 

};

#endif