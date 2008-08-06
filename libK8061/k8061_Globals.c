#include "k8061.h"

// Init global variables
int           _k8061_IsOpen[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
char          _k8061_ReadBuffer[50]  = {};
char          _k8061_WriteBuffer[50] = {};
unsigned char _k8061_jmp_adc[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned char _k8061_jmp_dac[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

usb_dev_handle* _k8061_Handle[8]  = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
