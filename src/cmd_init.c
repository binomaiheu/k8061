#include "cmd8061.h"
#include "k8061.h"

int cmd8061_done;
int cmd8061_card;

int cmd_init( void ) {

   printf( "Initializing interface...\n" );
   init_readline();
   
   printf( "Initializing k8061 USB devices...\n" );
   k8061_Init();

   // we're not done yet ;)
   cmd8061_done = 0;

   // set first card as default
   cmd8061_card = 0;

   // open the devices
   k8061_OpenDevices( );
}
