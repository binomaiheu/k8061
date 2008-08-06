#include "k8061.h"

int k8061_ScanBus( int verb ) {
  
  int n_open = 0;
  struct usb_bus *bus    = 0; 
  struct usb_device *dev = 0; 
  usb_dev_handle *dh     = 0;
  
  int tmp = 0, n_write = 0, n_read = 0;
  
  usb_find_busses();
  usb_find_devices();
  
  for ( bus = usb_busses; bus; bus = bus->next ) {
    for ( dev = bus->devices; dev; dev = dev->next ) {
      if ( ( dev->descriptor.idVendor  == k8061_idVendor  ) && 
           ( dev->descriptor.idProduct == k8061_idProduct ) ) {

	if ( verb > 1  ) {
	  printf( "Found a k8061 device at bus %s, dev %s\n", dev->bus->dirname, dev->filename );
	  fflush( stdout );
	}

        // Open device handle 
        dh = usb_open( dev );
	if ( ! dh ) {
	  if ( verb ) {
	    fprintf( stderr, " - *** error <k8061_ScanBus> : %s\n", usb_strerror() );
	    fprintf( stderr, " - *** error <k8061_ScanBus> : Cannot open device handle\n" );
	    fflush( stderr );
	  }
	  continue;
	}

	// Set the configuration and claim the interface
	if ( usb_set_configuration(dh, k8061_iConfig ) < 0 ) { 
	  if ( verb > 0 ) fprintf( stderr, " - *** error <k8061_ScanBus> : %s\n", usb_strerror() );
	  fprintf( stderr, " - *** error <k8061_ScanBus> : Cannot set configuration \n" );
	  fflush( stderr );
	  if ( dh ) usb_close( dh );
	  continue;
	}

	// Claim the interface 
	if ( usb_claim_interface( dh, k8061_iClaim ) < 0 ) { 
	  if ( verb > 0 ) fprintf( stderr, " - *** error <k8061_ScanBus> : %s\n", usb_strerror() );
	  fprintf( stderr, " - *** error <k8061_ScanBus> : Cannot claim interface \n" );
	  fflush( stderr );
	  if ( dh ) usb_close( dh );
	  continue;
	}

	// set the command
	_k8061_WriteBuffer[0] = k8061_cmdJumpers;
          
	// write 1 byte for this command
	n_write = usb_bulk_write( dh, k8061_epWrite, _k8061_WriteBuffer, 1, k8061_ioTimeOut );
	usleep( k8061_ioWait );
	if ( n_write < 0 ) {
	  if ( verb > 0 ) fprintf( stderr, " - *** error <k8061_ScanBus> : %s\n", usb_strerror() );
	  fprintf( stderr, " - *** error <k8061_ScanBus> : Failed to write command to device\n");
	  fflush( stderr );
	  if ( dh ) usb_close( dh );
	  continue;
	}
	
	// read result
	n_read  = usb_bulk_read( dh, k8061_epRead, _k8061_ReadBuffer, 2, k8061_ioTimeOut );
	usleep( k8061_ioWait );
	if ( n_read < 0 ) {
	  if ( verb > 0 ) fprintf( stderr, " - *** error <k8061_ScanBus> : %s\n", usb_strerror() );
	  fprintf( stderr, " - *** error <k8061_ScanBus> : Failed to read back from device\n");
	  fflush( stderr );
	  if ( dh ) usb_close( dh );
	  continue;
	}

	// Succesful read
	tmp = (int) _k8061_ReadBuffer[1];
	if ( tmp < 0 || tmp > 7 ) {
	  fprintf( stderr, 
		   "*** error <k8061_OpenDevices> : Invalid device address (%d) in %s\n",
		   tmp, dev->filename );
	  fflush( stderr );
	  if ( dh ) usb_close( dh );
	} else {
	  // add the filehandle to the list
	  if ( ( _k8061_IsOpen[tmp] == 1 ) && ( _k8061_Handle[tmp] )  ) {
	    fprintf( stderr, " - *** error : Card %d already exists, strange...", tmp );
	    if ( _k8061_Handle[tmp] ) usb_close( _k8061_Handle[tmp] );
	  }
	  _k8061_IsOpen[tmp] = 1;
	  _k8061_Handle[tmp] = dh;
	  
	  // increment the succesfully opened devices
	  n_open++;
	  if ( verb > 1 ) printf( " - " );
	  if ( verb > 0 ) printf( "Succesfully found K8061 card nr %d\n", tmp );
	}
	

	
	
      } else {
	if ( verb > 1 ) {
	  printf( "Found other USB device at bus %s, dev %s\n", dev->bus->dirname, dev->filename );
	  fflush( stdout );
	}
      }


    }
  }

  return 0;
}
