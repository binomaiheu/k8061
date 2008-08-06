#include "k8061.h"

int k8061_OutputAllAnalog( int iCard, int value_arr[] ) {

  int i = 0;

  _k8061_WriteBuffer[0] = k8061_cmdSetAllAnalog;
  for ( i=0; i<8; i++ ) {

    if ( value_arr[i] < 0 ) {
      _k8061_WriteBuffer[i+1] = 0;
    } else if ( value_arr[i] > 255 ) {
      _k8061_WriteBuffer[i+1] = 255;
    } else {
      _k8061_WriteBuffer[i+1] = value_arr[i];
    }
  }
  
  return k8061_ExecIO( iCard, 9, 2 );
}
