/*
  Tell the GNU Readline library how to complete.  We want to try to
  complete on command names if this is the first word in the line, or
  on filenames if not. 
*/
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "cmd8061.h"


void init_readline ( void ) {
  /* Allow conditional parsing of the ~/.inputrc file. */
  rl_readline_name = "cmd8061";
  
  /* Tell the completer that we want a crack first. */
  rl_attempted_completion_function = cmd_completion;
}


/* Attempt to complete on the contents of TEXT.  START and END
   bound the region of rl_line_buffer that contains the word to
   complete.  TEXT is the word to complete.  We can use the entire
   contents of rl_line_buffer in case we want to do some simple
   parsing.  Returnthe array of matches, or NULL if there aren't any. */
char** cmd_completion ( const char* text, int start, int end ) {
  char **matches;

  matches = (char **)NULL;

  /* If this word is at the start of the line, then it is a command
     to complete.  Otherwise it is the name of a file in the current
     directory. */
  if (start == 0)
    matches = rl_completion_matches (text, cmd_generator);

  return (matches);
}

/* Generator function for command completion.  STATE lets us
   know whether to start from scratch; without any state
   (i.e. STATE == 0), then we start at the top of the list. */
char* cmd_generator (const char* text, int state ) {
  static int list_index, len;
  char *name;

  /* If this is a new word to complete, initialize now.  This
     includes saving the length of TEXT for efficiency, and
     initializing the index variable to 0. */
  if (!state)
    {
      list_index = 0;
      len = strlen (text);
    }

  /* Return the next name which partially matches from the
     command list. */
  while (name = cmd8061_commands[list_index].name)
    {
      list_index++;

      if (strncmp (name, text, len) == 0)
        return (dupstr(name));
    }

  /* If no names matched, then return NULL. */
  return ((char *)NULL);
}
