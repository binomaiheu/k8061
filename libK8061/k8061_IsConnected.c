#include "k8061.h"

int k8061_IsConnected( int iCard ) {
  
  if ( iCard < 1 || iCard > 8 ) {
    fprintf( stderr, "*** error <k8061_IsConnected> : Card number out of range...\n" );
    fflush( stderr );
    return -1;
  }

  return _k8061_IsOpen[ iCard ];
}

