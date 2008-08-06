#include "k8061.h"

int k8061_ReadDigitalChannel( int iCard, int iChan ) {
 
  _k8061_WriteBuffer[0] = k8061_cmdReadDigitalByte;
  if ( iChan < 1 || iChan > 8 ) {
    fprintf( stderr, "*** error <k8061_ReadDigitalChannel> : Channel number out of range...\n" );
    fflush( stderr );
    return -1;
  }

  if ( k8061_ExecIO( iCard, 1, 2 ) < 0 ) return -1;

  return ((unsigned char) _k8061_ReadBuffer[1]) & (1 << (iChan - 1));
}
