#include "k8061.h"

void k8061_CheckOpen( int iCard ) {

  // performs a quick r&w to see wheather the card is really open...
  // no output, but updates the arrays
  int n_read, n_write;
  

  if ( iCard < 0 || iCard > 7 ) {
    fprintf( stderr, "*** error <k8061_CheckOpen> : Card number out of range %d...\n", iCard );
    fflush( stderr );
    return;
  }

  if ( _k8061_Handle[ iCard ] ) {
    _k8061_WriteBuffer[0] = k8061_cmdJumpers;
    n_write = usb_bulk_write( _k8061_Handle[iCard] ,k8061_epWrite, _k8061_WriteBuffer, 1, 
			      k8061_ioTimeOut );
    usleep( k8061_ioWait );
    n_read = usb_bulk_read( _k8061_Handle[iCard] ,k8061_epRead, _k8061_ReadBuffer, 2, 
			    k8061_ioTimeOut );
    usleep( k8061_ioWait );
    if ( n_write < 0 || n_read < 0 ) {
      // nope, it's screwed
      if ( _k8061_Handle[iCard] ) usb_release_interface( _k8061_Handle[iCard], k8061_iClaim );
      if ( _k8061_Handle[iCard] ) usb_close( _k8061_Handle[ iCard ] );
      _k8061_IsOpen[iCard] = 0;
      _k8061_Handle[iCard] = NULL;
    } else {
      if ( iCard != (int) _k8061_ReadBuffer[1] ) {
	// card number doesn't match...
	fprintf( stderr, "*** error <k8061_CheckOpen> : Card number doesn't match with hardware\n");
	fprintf( stderr, "*** error <k8061_CheckOpen> : Found %d, expected %d\n", 
		 (int) _k8061_ReadBuffer[1], iCard );
	fflush( stderr );
	if ( _k8061_Handle[iCard] ) usb_release_interface( _k8061_Handle[iCard], k8061_iClaim );
	if ( _k8061_Handle[iCard] ) usb_close( _k8061_Handle[ iCard ] );
	_k8061_IsOpen[iCard] = 0;
	_k8061_Handle[iCard] = NULL;
      } else _k8061_IsOpen[iCard] = 1; // yep, all fine :)
    }
  } else {
    // nope, it's screwed, don't even have a handle
    _k8061_IsOpen[iCard] = 0;
  }

  return;
}
