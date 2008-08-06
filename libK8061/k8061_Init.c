#include "k8061.h"

void k8061_Init( void ) {

  int i = 0;

  // Initialise libusb
  usb_init();

  // Close all filehandles
  for ( i=0; i<8; i++ ) {
    _k8061_IsOpen[i] = 0;
    _k8061_Handle[i] = NULL;
  }
  
  // Reset buffers
  for ( i=0; i<50; i++ ) {
    _k8061_ReadBuffer[i] = 0;
    _k8061_WriteBuffer[i] = 0;
  }
  
  return;
}
