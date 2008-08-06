#include <string.h>
#include <stdlib.h>

#include "cmd_argparser.h"
#include "cmd8061.h"


// allocate a new variable
var_t*  new_var( void ) {
  var_t *v;
  v = (var_t*) malloc( sizeof(var_t) );
  if ( ! v ) {
    fprintf( stderr, "*** error: Cannot allocate memory for variable\n" );
    fflush( stderr );
    return NULL;
  }
  v->next = NULL;
  v->prev = NULL;

  v->sValue = NULL;
  v->dValue = 0.0;
  v->iValue = 0;
  v->hValue = 0;

  return v;
}

// get the arguments into a variable list
var_t* get_args( char *arg, int *n_arg ) {
  
  char *a, *p;

  var_t *v     = NULL;
  var_t *vlist = NULL;
  *n_arg = 0;

  if ( ! arg ) return NULL;

  a = arg;
  while ( p = strtok( a, SEPSTR ) ) {
    a = NULL;
    
    v = new_var( );
    v->sValue = p;
    v->dValue = strtod( p, &(v->dErr) );
    v->iValue = strtol( p, &(v->iErr), 10 );
    v->hValue = strtoul( p, &(v->hErr), 16 );
    push_var( &vlist, v );
    (*n_arg)++;
  }

  return vlist;
}

// push a variable to the list
void push_var( var_t** vlist, var_t *v ) {

  var_t *b;

  if ( ! *vlist ) *vlist = v; 
  else {
    b = *(vlist);
    while ( b->next ) b = b->next;
    b->next = v;
    v->prev = b;
  }

  return;
}

// print variable list
void print_vlist( var_t *vlist ) {

  int    iv = 1;
  var_t  *v;

  printf ( "Variable list :\n" );
  v = vlist;
  while ( v ) {
    printf( "Var%d : dValue = %f, iValue = %d, hValue = 0x%x, sValue = %s\n", iv++,
	    v->dValue, v->iValue, v->hValue, v->sValue );
    v = v->next;
  }
  
  return;
}

// free variable list
void free_vlist( var_t *vlist ) {
  
  var_t *v = vlist;

  while ( v->next ) {
    v = v->next;
    free( v->prev );
  }
  free( v );

  return;
}


