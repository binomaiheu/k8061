#include "k8061.h"


int k8061_HasPower( int iCard ) {

  _k8061_WriteBuffer[0] = k8061_cmdPowerStatus;
  if ( k8061_ExecIO( iCard, 1, 2 ) < 0 ) {
    fprintf( stderr, "*** error <k8061_HasPower> : Cannot execute IO command on %d...\n", iCard );
    fflush( stderr );
    return -1;
  }

  return (int) _k8061_ReadBuffer[1];
}
