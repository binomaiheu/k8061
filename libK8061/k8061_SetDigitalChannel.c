#include "k8061.h"

int k8061_SetDigitalChannel( int iCard, int iChan ) {

  unsigned char b;

  if ( iChan < 1 || iChan > 8 ) {
    fprintf( stderr, "*** error <k8061_SetDigitalChannel> : Channel number out of range...\n" );
    fflush( stderr );
    return -1;
  }

  b = 1 << (iChan - 1 );

  _k8061_WriteBuffer[0] = k8061_cmdSetDigitalChannel;
  _k8061_WriteBuffer[1] = b;

  // send 2 bytes, receive 3
  return k8061_ExecIO( iCard, 2, 3 );  
}
