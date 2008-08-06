#include <stdlib.h>
#include "cmd8061.h"

char* stripwhite ( char* string) {
  register char *s, *t;
  
  for ( s = string; whitespace(*s); s++ );
  
  if (*s == 0 ) return ( s );

  t = s + strlen (s) - 1;
  while (t > s && whitespace( *t ) ) t--;
  *++t = '\0';
  
  return s;
}


char* dupstr( char* s ) {

  char *r;
  r = (char*) malloc( strlen( s ) + 1 );
  if ( ! r ) {
    fprintf( stderr, "*** (%s <%d>) memory allocation error in dupstr\n", __FILE__, __LINE__ );
    fflush( stderr );
    exit( 1 );
  }
  strcpy ( r, s );
  return (r);
}

int chomp( char *s ) {

  if ( s && *s ) {
    s += strlen( s ) - 1;
    if ( *s == '\n' ) {
      *s = 0;
      return 1;
    }
  }
  return 0;
}
