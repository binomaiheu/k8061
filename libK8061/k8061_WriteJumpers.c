#include "k8061.h"

int k8061_WriteJumpers( int iCard, FILE *fp ) {

  int i=0;
  int mask = 1;

  if ( ! fp ) return -1;

  if ( iCard < 0 || iCard > 7 ) {
    fprintf( stderr, "*** error <k8061_WriteJumpers> : Card number out of range...\n" );
    fflush( stderr );
    return -1;
  }

  fprintf( fp, "AIN Jumper Config 1->8: " );
  for ( i=0; i<8; i++ ) {
    fprintf( fp, "%d ", ( _k8061_jmp_adc[iCard] & mask ) >> i );
    mask = mask << 1;
  }
  fprintf( fp, "\n" );

  mask = 1;
  fprintf( fp, "AOUT Jumper Config 1->8: " );
  for ( i=0; i<8; i++ ) {
    fprintf( fp, "%d ", ( _k8061_jmp_dac[iCard] & mask ) >> i );
    mask = mask << 1;
  }
  fprintf( fp, "\n" );
  fflush( fp );

  return 0;
}
