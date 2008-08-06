#include "k8061.h"

int k8061_ReadBackDigitalOut( int iCard, int dout_arr[] ) {

  char dout = 0;
  int i = 0, mask = 1;

  _k8061_WriteBuffer[0] = k8061_cmdReadDigitalOut;
  if ( k8061_ExecIO( iCard, 1, 2 ) < 0 ) {
    fprintf( stderr, "*** error <k8061_ReadBackDigitalOut> : Cannot execute IO command on %d...\n",
	     iCard );
    fflush( stderr );
    return -1;
  }

  dout = _k8061_ReadBuffer[1];
  // break up the byte, bit of a waste, but more user friendly for dummies :D
  // assume digitalOut[8]
  for ( i = 0; i<8; i++ ) {
    dout_arr[i] = (unsigned char) ( dout & mask ) >> i;
    mask <<= 1;
  }

  return 0;
}
