#include "k8061.h"

int k8061_SetAllAnalog( int iCard ) {

  int i = 0;

  _k8061_WriteBuffer[0] = k8061_cmdSetAllAnalog;
  for ( i=0; i<8; i++ ) _k8061_WriteBuffer[i+1] = 255;
  
  return k8061_ExecIO( iCard, 9, 2 );
}
