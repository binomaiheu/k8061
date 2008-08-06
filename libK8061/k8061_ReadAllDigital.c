#include "k8061.h"

int k8061_ReadAllDigital( int iCard, int din_arr[] ) {

  unsigned char din;
  int i = 0, mask = 1;

  _k8061_WriteBuffer[0] = k8061_cmdReadDigitalByte;

  if ( k8061_ExecIO( iCard, 1, 2 ) < 0 ) {
    fprintf( stderr, "*** error <k8061_ReadAllDigital> : Cannot execute IO command on %d...\n",
             iCard );
    fflush( stderr );
    return -1;
  }

  din = (unsigned char) _k8061_ReadBuffer[1];

  // set din array
  for ( i = 0; i<8; i++ ) {
    din_arr[i] = (unsigned char) ( din & mask ) >> i;
    mask <<= 1;
  }
  
  return 0;
}
