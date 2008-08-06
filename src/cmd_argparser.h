#ifndef ARGPARSER_H
#define ARGPARSER_H

#define SEPSTR " ,:;\t\n"

typedef struct var var_t;

struct var {
  var_t *next;
  var_t *prev;

  char         *sValue;  // string value

  double         dValue;  // floaint point value
  char          *dErr;

  int            iValue;  // integer value
  char          *iErr;

  unsigned long   hValue;  // hex word value
  char           *hErr;    // err pointer from strtoul
};

extern var_t*  new_var( void );
extern void    push_var( var_t** vlist, var_t* v );
extern var_t*  get_args( char *arg, int *n_arg );
extern void    print_vlist( var_t *vlist );
extern void    free_vlist( var_t *vlist );

#endif
