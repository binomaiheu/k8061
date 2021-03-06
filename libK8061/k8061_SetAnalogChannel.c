#include "k8061.h"

int k8061_SetAnalogChannel( int iCard, int iChan ) {
  
  if ( iChan < 1 || iChan > 8 ) {
    fprintf( stderr, "*** error <k8061_SetAnalogChannel> : Channel number out of range...\n" );
    fflush( stderr );
    return -1;
  }

  _k8061_WriteBuffer[0] = k8061_cmdSetAnalogChannel;
  _k8061_WriteBuffer[1] = iChan - 1;
  _k8061_WriteBuffer[2] = 255;
  
  return k8061_ExecIO( iCard, 3, 4 );
}
