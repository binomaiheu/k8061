#include "k8061.h"

int k8061_OutputAllDigital( int iCard, unsigned char bPattern ) {

  _k8061_WriteBuffer[0] = k8061_cmdDigitalOut;
  _k8061_WriteBuffer[1] = bPattern;

  // send 2 bytes, receive 3
  return k8061_ExecIO( iCard, 2, 3 );  
}
