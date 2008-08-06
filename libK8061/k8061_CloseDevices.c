#include "k8061.h"

void k8061_CloseDevices( void ) {
  
  int iaddr = 0;

  for ( iaddr = 0; iaddr < 7; iaddr++ ) {
    if ( _k8061_Handle[iaddr] ) {
      if ( usb_close( _k8061_Handle[iaddr] ) < 0 ) {
	fprintf( stderr, "*** %s\n", usb_strerror() );
	fprintf( stderr, "*** error (k8061_CloseDevices) : error closing device %d", iaddr );
	fflush( stderr );
      } else {
	printf( "Closed k8061 device %d\n", iaddr );
	fflush( stdout );
      }
    }
  }


  return;
}
