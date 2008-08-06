#include "k8061.h"

void k8061_ListDevices( FILE* fp ) {

  int iCard = 0;

  for ( iCard = 0; iCard < 8 ; iCard++ ) {
    if ( _k8061_IsOpen[iCard] ) {
      fprintf( fp, "Card %d, ", iCard );
      k8061_WriteStatus( iCard, fp );
    } else {
      fprintf( fp, "Card %d not found on USB bus \n", iCard );
    }
  }
  fflush( fp );
  return;
}
