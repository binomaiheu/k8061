#include "k8061.h"

int k8061_ReadBackAnalogOut( int iCard, int aout_arr[] ) {

  int i = 0;

  _k8061_WriteBuffer[0] = k8061_cmdReadAnalogOut;
  if ( k8061_ExecIO( iCard, 1, 9 ) < 0 ) {
    fprintf( stderr, "*** error <k8061_ReadBackAnalogOut> : Cannot execute IO command on %d...\n",
	     iCard );
    fflush( stderr );
    return -1;
  }

  for ( i = 0; i<8; i++ ) aout_arr[i] = (unsigned char) _k8061_ReadBuffer[i+1];

  return 0;
}
