#include "k8061.h"

int k8061_ReadAnalogChannel( int iCard, int iChan ) {

  _k8061_WriteBuffer[0] = k8061_cmdReadAnalogChannel;
  if ( iChan < 1 || iChan > 8 ) {
    fprintf( stderr, "*** error <k8061_ReadAnalogChannel> : Channel number out of range...\n" );
    fflush( stderr );
    return -1;
  }
  
  _k8061_WriteBuffer[1] = iChan - 1;
  if ( k8061_ExecIO( iCard, 2, 4 ) < 0 ) return -1;
  
  return (unsigned char) _k8061_ReadBuffer[2] + 256*(unsigned char)_k8061_ReadBuffer[3];
}
