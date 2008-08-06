/**
   The k8061 Command-line Interface

   Written by Bino Maiheu
*/
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "cmd8061.h"


int main( int argc, char **argv ) {

 char *line, *s;
 char prompt[30];

 printf( "cmd8061 Copyright (C) 2008  Bino Maiheu \n");
 printf( "A linux based command-line interface for the\n" );
 printf( "Velleman K8061 Extended USB Interface\n\n" );
 printf( "This program comes with ABSOLUTELY NO WARRANTY;\n");
 printf( "This is free software, and you are welcome to redistribute it\n");
 printf( "under conditions set out in the GNU General Public Licence version 2\n" );
 printf( "See: http://www.gnu.org/licenses\n\n" ); 

 if ( cmd_init( ) < 0 ) return 1;
 
 for (  ;cmd8061_done == 0; ) {

   sprintf( prompt, "cmd8061::%d> ", cmd8061_card );
   line = readline ( prompt );
      
   if ( ! line ) break;

   // remove whitespaces at front & after
   s = stripwhite (line);

   // if some chars are left... execute it !
   if ( *s ) {
     add_history( s );
     cmd_execute( s );
   }

   free (line);
   fflush( stdout );
   fflush( stderr );

   // check the k8061 devices on the usb bus before doing the next line...
   // ...
   // ...
 }
 
 cmd_cleanup( );
 
 return 0;
}
