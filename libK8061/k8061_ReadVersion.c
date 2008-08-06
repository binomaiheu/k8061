#include <string.h>

#include "k8061.h"

int k8061_ReadVersion( int iCard, char version_str[] ) {
  
  int  i = 0;
  char p[51] = "";

  _k8061_WriteBuffer[0] = k8061_cmdReadVersion;
  if ( k8061_ExecIO( iCard, 1, 49 ) < 0 ) {
    fprintf( stderr, "*** error <k8061_HasPower> : Cannot execute IO command on %d...\n", iCard );
    fflush( stderr );
    return -1;
  }

  for ( i=1;  i<25; i++ ) p[i-1] = _k8061_ReadBuffer[i];
  p[24] = ',';
  p[25] = ' ';
  for ( i=25; i<49; i++ ) p[i+1] = _k8061_ReadBuffer[i];

  // copy the string to ver... hope it's big enough :)
  strncpy( version_str, p, 51 );

  return 0;
}
