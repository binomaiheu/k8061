#include "k8061.h"

int k8061_ClearAllDigital( int iCard ) {

  _k8061_WriteBuffer[0] = k8061_cmdDigitalOut;
  _k8061_WriteBuffer[1] = 0x0; // or: 0000 0000

  // send 2 bytes, receive 3
  return k8061_ExecIO( iCard, 2, 3 );  
}
