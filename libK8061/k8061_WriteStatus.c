#include "k8061.h"

int k8061_WriteStatus( int iCard, FILE* fp ) {

  char ver[60];
  int hp = 0;

  if ( ! fp ) return -1;

  if ( iCard < 0 || iCard > 7 ) {
    fprintf( stderr, "*** error <k8061_WriteStatus> : Card number out of range...\n" );
    fflush( stderr );
    return -1;
  }

  k8061_CheckOpen( iCard );

  if ( _k8061_IsOpen[iCard] ) {

    fprintf( fp, "connected");
    hp = k8061_HasPower( iCard );
    if ( hp < 0 ) {
      fprintf( stderr, "\n*** error <k8061_WriteStatus> : cannot get power status...\n" );
      fflush( stderr );
      return -1;
    } else if ( hp == 0 ) {
      fprintf( fp, ", power off\n" );
    } else {
      fprintf( fp, ", power on" );
      if ( k8061_ReadVersion( iCard, ver ) < 0 ) {
	fprintf( stderr, "\n*** error <k8061_WriteStatus> : cannot get firmware version...\n" );
	fflush( stderr );
	return -1;
      }
      fprintf( fp, ", version : %s\n", ver );
    }
  } else {
    fprintf( fp, "not connected\n");
  }

  fflush( fp );
  
  return 0;
}
