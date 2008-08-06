#ifndef CMD8061_H
#define CMD8061_H

#include <stdio.h>
#include <readline/readline.h>

// cmd_commands
typedef struct {
  char           *name;	   /* User printable name of the function. */
  rl_icpfunc_t   *func;    /* Function to call to do the job. */
  char           *argdoc;  /* Explanation of arguments */
  char           *doc;	   /* Documentation for this function.  */
} cmd_t;


extern cmd_t  cmd8061_commands[]; /**< The commands know to the interpreter */
extern cmd_t *cmd_find( char* name ); /**< find the command */

// command list
extern int    cmd_scan( char* arg );
extern int    cmd_stat( char* arg );
extern int    cmd_card( char* arg );
extern int    cmd_help( char* arg );
extern int    cmd_quit( char* arg );
extern int    cmd_list( char* arg );
extern int    cmd_wait( char* arg );
extern int    cmd_get( char* arg );
extern int    cmd_set( char *arg );
extern int    cmd_jmps( char *arg );
extern int    cmd_info( char* arg );
extern int    cmd_exec( char* arg );
extern int    cmd_reset( char *arg );
extern int    cmd_clr( char *arg );
extern int    cmd_err( char *arg );


// cmd_execute
extern int    cmd_execute( char *line );

// cmd_init & cleanup
extern int    cmd8061_done;
extern int    cmd8061_card;
extern int    cmd_init( void );
extern void   cmd_cleanup( void );

// cmd_completion routines
extern void   init_readline( void );
extern char*  cmd_generator( const char *text, int state );
extern char** cmd_completion( const char *text, int start, int end ); 

// cmd_strmanip routines
extern char*  stripwhite ( char* string );
extern char*  dupstr( char *s  );
extern int    chomp( char *s );

#endif /* #ifndef CMD8061_H */
