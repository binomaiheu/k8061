#include "k8061.h"

int k8061_ReadBackPWMOut( int iCard ) {

  _k8061_WriteBuffer[0] = k8061_cmdReadPWMOut;
  if ( k8061_ExecIO( iCard, 1, 3 ) < 0 ) {
    fprintf( stderr, "*** error <k8061_ReadBackPWMOut> : Cannot execute IO command on %d...\n",
	     iCard );
    fflush( stderr );
    return -1;
  }

  return (unsigned char) _k8061_ReadBuffer[1] + 4 * (unsigned char) _k8061_ReadBuffer[2];
}
