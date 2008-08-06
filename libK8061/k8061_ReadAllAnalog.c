#include "k8061.h"

int k8061_ReadAllAnalog( int iCard, int value_arr[] ) {

  int i = 0;

  _k8061_WriteBuffer[0] = k8061_cmdReadAllAnalog;

  if ( k8061_ExecIO( iCard, 1, 17 ) < 0 ) return -1;
  
  for ( i=0; i<8; i++ ) {
    value_arr[i] = (unsigned char) _k8061_ReadBuffer[2*i+1] + 
      256*(unsigned char)_k8061_ReadBuffer[2*i+2];
  }

  return 0;
}
