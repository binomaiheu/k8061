#include "k8061.h"

int k8061_OutputAnalogChannel( int iCard, int iChan, int value ) {
  
  if ( iChan < 1 || iChan > 8 ) {
    fprintf( stderr, "*** error <k8061_OutputAnalogChannel> : Channel number out of range...\n" );
    fflush( stderr );
    return -1;
  }

  _k8061_WriteBuffer[0] = k8061_cmdSetAnalogChannel;
  _k8061_WriteBuffer[1] = iChan - 1;

  if ( value < 0 ) {
    _k8061_WriteBuffer[2] = 0;
  } else if ( value > 255 ) {
    _k8061_WriteBuffer[2] = 255;
  } else {
    _k8061_WriteBuffer[2] = value;
  }
  
  return k8061_ExecIO( iCard, 3, 4 );
}
