#include "k8061.h"

int k8061_ExecIO( int iCard, int nSend, int nReceive ) {

  int n_write = 0, n_read = 0;

  if ( iCard < 0 || iCard > 7 ) {
    fprintf( stderr, "*** error <k8061_ExecIO> : Card number out of range %d...\n", iCard );
    fflush( stderr );
    return -1;
  }

  if ( _k8061_IsOpen[iCard] ) {
    n_write = usb_bulk_write( _k8061_Handle[iCard] ,k8061_epWrite, _k8061_WriteBuffer, 
			      nSend, k8061_ioTimeOut );
    usleep( k8061_ioWait );
    if ( n_write < 0 ) {
      fprintf( stderr, "*** %s\n", usb_strerror() );
      fprintf( stderr, "*** error <k8061_ExecIO> : Error writing command to card %d\n", iCard );
      fflush( stderr );

      if ( _k8061_Handle[iCard] ) usb_release_interface( _k8061_Handle[iCard], k8061_iClaim );
      if ( _k8061_Handle[iCard] ) usb_close( _k8061_Handle[iCard] );
      _k8061_IsOpen[iCard] = 0;
      
      return -1;
    } 
    
    n_read = usb_bulk_read( _k8061_Handle[iCard] ,k8061_epRead, _k8061_ReadBuffer, 
			    nReceive, k8061_ioTimeOut );
    usleep( k8061_ioWait );
    if ( n_read < 0 ) {
      fprintf( stderr, "*** %s\n", usb_strerror() );
      fprintf( stderr, "*** error <k8061_ExecIO> : Error reading buffer from card %d\n", iCard );
      fflush( stderr );

      if ( _k8061_Handle[iCard] ) usb_release_interface( _k8061_Handle[iCard], k8061_iClaim );
      if ( _k8061_Handle[iCard] ) usb_close( _k8061_Handle[iCard] );
      _k8061_IsOpen[iCard] = 0;

      return -1;
    } 

  } else {
    fprintf( stderr, "*** error <k8061_ExecIO> : Card %d not found/not opened...\n", iCard );
    fflush( stderr );
    return -1;
  }
    
  return 0;
}
