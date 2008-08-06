#include "k8061.h"
#include "cmd8061.h"


void cmd_cleanup( void ) {

  k8061_CloseDevices();

  return;
}
