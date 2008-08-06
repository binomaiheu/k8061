#include "k8061.h"

int k8061_ReadAllDigitalByte( int iCard, unsigned char *din_byte ) {

  _k8061_WriteBuffer[0] = k8061_cmdReadDigitalByte;

  if ( k8061_ExecIO( iCard, 1, 2 ) < 0 ) {
    fprintf( stderr, "*** error <k8061_ReadAllDigitalByte> : Cannot execute IO command on %d...\n",
             iCard );
    fflush( stderr );
    return -1;
  }

  *din_byte = (unsigned char) _k8061_ReadBuffer[1];
  
  return 0;
}
