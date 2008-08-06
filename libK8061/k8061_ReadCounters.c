#include "k8061.h"

int k8061_ReadCounters( int iCard, int cntr_arr[] ) {
  
  int i = 0;

  _k8061_WriteBuffer[0] = k8061_cmdReadCounters;
  
  if ( k8061_ExecIO( iCard, 1, 5 ) ) return -1;
  for ( i=0; i<2; i++ ) {
    cntr_arr[i] = (unsigned char) _k8061_ReadBuffer[2*i+1] + 
      256 * (unsigned char) _k8061_ReadBuffer[2*2+2];
  }
  
  return 0;
}
