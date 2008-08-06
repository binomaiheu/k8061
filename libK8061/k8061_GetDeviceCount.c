#include "k8061.h"

int k8061_GetDeviceCount( void ) {

  int n = 0; // the number of K8061 devices found
  struct usb_bus    *bus    = 0; // a USB bus structure ( libusb )
  struct usb_device *dev    = 0; // a USB device structure ( libusb )
  usb_dev_handle    *handle = 0;

  usb_find_busses();
  usb_find_devices();

  for ( bus = usb_busses; bus; bus = bus->next ) {
    for ( dev = bus->devices; dev; dev = dev->next ) {

      
      if ( ( dev->descriptor.idVendor  == k8061_idVendor  ) && 
	   ( dev->descriptor.idProduct == k8061_idProduct ) ) {
        handle = usb_open( dev );
	if ( handle ) {
	  n++; 
	  if ( usb_close( handle ) < 0 ) {
	    fprintf( stderr, "+++ warning: K8061 device found at %s, opened, but unable to close", 
		     dev->filename );
	    fprintf( stderr, "    %s\n", usb_strerror() );
	    fflush( stderr );
	  }
	} else {
	  fprintf( stderr, "+++ warning: K8061 device found at %s, but unable to open", 
		   dev->filename );
	  fprintf( stderr, "    %s\n", usb_strerror() );
	  fflush( stderr );
	}
      }


    }
  }
  
  return n;
}
