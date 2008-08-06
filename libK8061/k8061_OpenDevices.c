#include "k8061.h"

int k8061_OpenDevices( void ) {

  return k8061_ScanBus( 1 );
}
