#include "cmd8061.h"

int cmd_execute( char * line ) {
  register int i;
  cmd_t *command;
  char *word;

  /* Isolate the command word. */
  i = 0;
  while (line[i] && whitespace (line[i]))
    i++;
  word = line + i;

  while (line[i] && !whitespace (line[i]))
    i++;

  if (line[i])
    line[i++] = '\0';

  command = cmd_find( word );
  
  if ( ! command ) {
    fprintf (stderr, "*** error: unknown command '%s' \n", word );
    return -1;
  }

  /* Get argument to command, if any. */
  while (whitespace (line[i]))
    i++;

  word = line + i;

  /* Call the function. */
  return ((*(command->func)) (word));
}
