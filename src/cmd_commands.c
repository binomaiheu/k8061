#include <limits.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "cmd8061.h"
#include "k8061.h"

#include "cmd_argparser.h"

cmd_t cmd8061_commands[] = {
  { "scan", cmd_scan, "                  ", "Scan usb bus and update k8061 array." },
  { "list", cmd_list, "                  ", "List of known k8061 devices on USB bus" },
  { "stat", cmd_stat, "                  ", "Show status of the active k8061 card." },
  { "card", cmd_card, "<icard>           ", "Select an active k8061 card on USB bus [0-7]." },
  { "get",  cmd_get,  "<grp> [ch]        ", "Get value of channel of group" },
  { "set",  cmd_set,  "<grp> <ch> <v> [V]", "Set value of channel of group to v, [AOUT in Volt]" },
  { "reset",cmd_reset,"                  ", "Resets the board, output values to 0" },
  { "clr",  cmd_clr,  "                  ", "Clear read errors" },
  { "err",  cmd_err,  "                  ", "Show read errors" },
  { "jmps", cmd_jmps, "<grp> <hex>       ", "Set jumper values for analog in/out groups" },
  { "wait", cmd_wait, "<secs>            ", "Wait for a number of seconds." },
  { "exec", cmd_exec, "<fname>           ", "Execute the file with commands" },
  { "quit", cmd_quit, "                  ", "Quit this program." },
  { "help", cmd_help, "                  ", "Display help text on the commands" },
  { "info", cmd_info, "                  ", "Display some usefull info about the program" },
  { (char *)NULL, (rl_icpfunc_t *)NULL, (char *)NULL }
};

// Find a command --------------------------------------------------------------
cmd_t *cmd_find( char* name ) { 
  register int i;
  
  for (i = 0; cmd8061_commands[i].name; i++)
    if (strcmp (name, cmd8061_commands[i].name) == 0)
      return (&cmd8061_commands[i]);

  return ((cmd_t *)NULL);
}


// Implementation of the command functions -------------------------------------

int cmd_clr( char *arg ) {
  printf( "Clearing read errors\n" );
  return k8061_ResetCounters( cmd8061_card );
}

int cmd_err( char *arg ) {
  int er[2];
  k8061_ReadCounters( cmd8061_card, er );
  printf( "Read Errors 0 : %d \n", er[0] );
  printf( "Read Errors 1 : %d \n", er[1] );
  return 0;
}


/* --- print some info --- */
int cmd_info ( char* arg ) {
  
  printf( "Groups on the board are :\n" );
  printf( "   - dout ..... : digital outputs\n" );
  printf( "   - aout ..... : analog outputs\n" );
  printf( "   - din ...... : digital inputs\n" );
  printf( "   - ain ...... : analog inputs\n" );
  printf( "   - pwm ...... : pulser\n" );
  
  return 0;
}



/* --- reset the board --- */
int cmd_reset( char *arg ) {
  
  char cmd[80];

  strcpy( cmd, "clr" ); if ( cmd_execute( cmd) < 0 ) return -1;
  strcpy( cmd, "set dout all 0" ); if ( cmd_execute( cmd) < 0 ) return -1;
  strcpy( cmd, "set aout all 0" ); if ( cmd_execute( cmd) < 0 ) return -1;
  strcpy( cmd, "set pwm 0" ); if ( cmd_execute( cmd) < 0 ) return -1;
  

  return 0;
}

/* --- print some help --- */
int cmd_help ( char* arg ) {
  register int i;
  int printed = 0;

  for (i = 0; cmd8061_commands[i].name; i++)  {
    if ( ! *arg || ( strcmp( arg, cmd8061_commands[i].name ) == 0 ) )  {
      printf ("%s\t%s\t%s.\n", cmd8061_commands[i].name,cmd8061_commands[i].argdoc, 
	      cmd8061_commands[i].doc);
      printed++;
    }
  }
  
  if ( ! printed ) {
      printf ("No commands match `%s'.  Possibilties are:\n", arg);

      for (i = 0; cmd8061_commands[i].name; i++)
        {
          /* Print in six columns. */
          if (printed == 6)
            {
              printed = 0;
              printf ("\n");
            }

          printf ("%s\t", cmd8061_commands[i].name);
          printed++;
        }

      if (printed)
        printf ("\n");
    }
  return (0);
}

/* --- scan usb bus --- */
int cmd_scan( char* arg ) {
  if ( k8061_ScanBus( 2 ) < 0 ) return -1;
  return 0;
}


/* --- quit the program --- */
int cmd_quit ( char* arg ) {
  cmd8061_done = 1;
  return 0;
}

/* --- show status --- */
int cmd_stat( char* arg ) {
  
  printf( "[Card %d Status]\n", cmd8061_card );
  k8061_WriteStatus( cmd8061_card, stdout );
  printf( "[Card %d Jumper Settings]\n", cmd8061_card );
  k8061_WriteJumpers( cmd8061_card, stdout );

  return 0;
}

/* --- list devices --- */
int cmd_list( char* arg ) {
  k8061_ListDevices( stdout );
  return 0;
}


/* --- show status --- */
int cmd_card( char* arg ) {

  int ic = 0;
  ic = atoi( arg );

  stripwhite( arg );
  if ( strlen( arg ) ) {
    if ( ic < 0 || ic > 7 ) {
      fprintf( stderr, "*** error: invalid card number '%s'\n", arg );
      return -1;
    } else {
      cmd8061_card = ic;
      printf( "Selected card %d\n", cmd8061_card );
    }
  } else {
    fprintf( stderr, "*** error: keyword 'card' expects an integer argument\n" );
    return -1;
  }
  
  // display card status
  return cmd_stat( arg );
}



/* --- set values to the board --- */
int cmd_set( char *arg ) {

  var_t  *vlist;
  int     n, all, iChan, value;
  int     i, val_arr[8];
  double  volt_arr[8];
  char    cmd[10];

  vlist = get_args( arg, &n );
  if ( n < 2 ) {
    fprintf( stderr, "*** error: keyword 'set' expects at least two arguments\n" );
    fflush( stderr );
    return -1;
  }
  
  if ( ( ! strcmp( vlist->sValue, "dout" ) ) || 
       ( ! strcmp( vlist->sValue, "aout" ) ) ) {
    
    strcpy( cmd, vlist->sValue );

    // read channel
    if ( ! vlist->next ) {
      fprintf( stderr, "*** error: 'set d/aout' commands expect 2 more integer arguments\n" );
      return -1;
    }
    vlist = vlist->next;
    if ( ! strcmp( vlist->sValue, "all" ) ) {
      all = 1;
    } else {
      all = 0;
      if ( vlist->iValue < 1 || vlist->iValue > 8 ) {
	fprintf( stderr, "*** error: invalid channel number '%s'\n", vlist->sValue );
	return -1;
      }
      iChan = vlist->iValue;
    }
    
    // read bit
    if ( ! vlist->next ) {
      fprintf( stderr, "*** error: 'set dout' command expects 2 more integer arguments\n" );
      return -1;
    }
    vlist = vlist->next;
    

    // now distinguish between AOUT and DOUT...
    if ( ! strcmp( cmd, "dout" ) ) {

      value = vlist->iValue;
    /* =====================
       Set DOUT values
       ================== */
	
      if ( value < 0 || value > 1 ) {
	fprintf( stderr, "*** error: a single bit is only 0 or 1 !\n" );
	return -1;
      }
      
      if ( all ) { 
	printf( "Setting all DOUT channels to %d on card %d\n", value, cmd8061_card );
	if ( value == 0 ) k8061_ClearAllDigital( cmd8061_card ); 
	else k8061_SetAllDigital( cmd8061_card  );
      } else {
	printf( "Setting DOUT channel %d to %d on card %d\n", iChan, value, cmd8061_card );
	if ( value == 0 ) k8061_ClearDigitalChannel( cmd8061_card, iChan ); 
	else  k8061_SetDigitalChannel( cmd8061_card, iChan );
      }
      
    } else {
      
      /* =====================
	 Set AOUT values
	 ================== */
      if ( vlist->next ) {
	// do we have "V" behind ?
	if ( ! strcmp( vlist->next->sValue, "V" ) || 
	     ! strcmp( vlist->next->sValue, "Volt" ) ) {
	  if ( all ) { 
	    printf( "Setting all AOUT channels to %.2f V on card %d\n", 
		    vlist->dValue, cmd8061_card );
	    for ( i = 0; i < 8; i++ ) volt_arr[i] = vlist->dValue;;
	    k8061_OutputAllAnalogVolt( cmd8061_card, volt_arr );
	  } else {
	    printf( "Setting AOUT channel %d to %.2f V on card %d\n", iChan, vlist->dValue, 
		    cmd8061_card );
	    k8061_OutputAnalogChannelVolt( cmd8061_card, iChan, vlist->dValue );
	  }

	} else {
	  fprintf( stderr, "*** error: only suffix 'V' or 'Volt' allowed to indicate voltage !\n");
	  return -1;
	}
      } else {
	// we just have an integer value
	value = vlist->iValue;
	if ( value < 0 ) {
	  fprintf( stderr, "*** warning: analog value < 0, setting to 0 !\n" );
	  value = 0;
	}
	
	if ( value > 255 ) {
	  fprintf( stderr, "*** warning: analog value > 255, setting to 255 !\n" );
	  value = 255;
	}
	
	if ( all ) { 
	  printf( "Setting all AOUT channels to %d on card %d\n", value, cmd8061_card );
	  for ( i = 0; i < 8; i++ ) val_arr[i] = value;
	  k8061_OutputAllAnalog( cmd8061_card, val_arr );
	} else {
	  printf( "Setting AOUT channel %d to %d on card %d\n", iChan, value, cmd8061_card );
	  k8061_OutputAnalogChannel( cmd8061_card, iChan, value );
	}
      }	
    }
  } else if ( ! strcmp( vlist->sValue, "pwm" ) ) {
	/* =====================
	   Set PWM values
	   ================== */
    
    if ( ! vlist->next ) {
      fprintf( stderr, "*** error: 'set pwm' command expects integer argument\n" );
      return -1;
    }
    
    if ( vlist->next->iValue < 0 ) {
      fprintf( stderr, "*** error: cannot have pwm < 0, setting to 0\n" );
      vlist->next->iValue = 0;
    }
    
    if ( vlist->next->iValue > 1023 ) {
      fprintf( stderr, "*** error: cannot have pwm > 1023, setting to 1023\n" );
      vlist->next->iValue = 1023;
    }
    
    printf( "Setting PWM to %d\n", vlist->next->iValue );
    k8061_OutputPWM( cmd8061_card, vlist->next->iValue );
    
  } else {
    fprintf( stderr, "*** error: unknown argument '%s' for set command\n", 
	     vlist->sValue );
    fflush( stderr );
    return -1;
  }

  return 0;
}

/* --- get values from the board --- */
int cmd_get( char *arg ) {

  var_t  *vlist;
  int     n, v;
  double  dv;
  int     out_arr[8];
  char    cmd[80];

  vlist = get_args( arg, &n );
  if ( n < 1 ) {
    fprintf( stderr, "*** error: keyword 'get' expects at least one argument\n" );
    fflush( stderr );
    return -1;
  }
  
  if ( ! strcmp( vlist->sValue, "all" ) ) {
    printf( "Getting all values for card %d\n", cmd8061_card );
    printf( "[Analog Input Group]\n" );
    strcpy( cmd, "get ain" ); cmd_execute( cmd ); 
    printf( "[Analog Output Group]\n" );
    strcpy( cmd, "get aout" ); cmd_execute( cmd ); 
    printf( "[Digital Input Group]\n" );
    strcpy( cmd, "get din" ); cmd_execute( cmd ); 
    printf( "[Digital Output Group]\n" );
    strcpy( cmd, "get dout" ); cmd_execute( cmd ); 
    printf( "[PWM Group]\n" );
    strcpy( cmd, "get pwm" ); cmd_execute( cmd ); 
  } else if ( ! strcmp( vlist->sValue, "pwm" ) ) {
    // read back PWM
    printf( "PWM = %d\n",  k8061_ReadBackPWMOut( cmd8061_card ) );
  } else if ( ! strcmp( vlist->sValue, "dout" ) ) {
    // read back digital out
    if ( k8061_ReadBackDigitalOut( cmd8061_card, out_arr ) < 0 ) return -1;
    if ( vlist->next ) {
      if ( vlist->next->iValue < 1 || vlist->next->iValue > 8 ) {
	fprintf( stderr, "*** error: invalid channel number '%d'\n", vlist->next->iValue );
	return -1;
      } else {
	printf( "DOUT %d = %d\n", vlist->next->iValue, out_arr[vlist->next->iValue-1] );
      }
    } else {
      for ( n=0;n<8;n++)
	printf( "DOUT %d = %d\n", n+1, out_arr[n] );
    }
  } else if ( ! strcmp( vlist->sValue, "aout" ) ) {
    // read back analog out
    if ( k8061_ReadBackAnalogOut( cmd8061_card, out_arr ) < 0 ) return -1;
    if ( vlist->next ) {
      if ( vlist->next->iValue < 1 || vlist->next->iValue > 8 ) {
	fprintf( stderr, "*** error: invalid channel number '%d'\n", vlist->next->iValue );
	return -1;
      } else {
	v  = out_arr[vlist->next->iValue-1];
	dv = k8061_GetDACVolt( cmd8061_card, vlist->next->iValue, v );
	printf( "AOUT %d = %d (%.2f V)\n", vlist->next->iValue, v, dv );
      }
    } else {
      for ( n=0;n<8;n++) {
	dv = k8061_GetDACVolt( cmd8061_card, n+1, out_arr[n] );
	printf( "AOUT %d = %d (%.2f V)\n", n+1, out_arr[n], dv );
      }
    }

  } else if ( ! strcmp( vlist->sValue, "ain" ) ) {
    // read analog input
    if ( vlist->next ) {
      if ( vlist->next->iValue < 1 || vlist->next->iValue > 8 ) {
	fprintf( stderr, "*** error: invalid channel number '%d'\n", vlist->next->iValue );
	return -1;
      } else {
	v  = k8061_ReadAnalogChannel( cmd8061_card, vlist->next->iValue);
	dv = k8061_GetADCVolt( cmd8061_card, vlist->next->iValue, v );
	printf( "AIN %d = %d (%.2f V)\n", vlist->next->iValue, v, dv );
      }
    } else {
      k8061_ReadAllAnalog( cmd8061_card, out_arr );
      for ( n=0;n<8;n++) {
	dv = k8061_GetADCVolt( cmd8061_card, n+1, out_arr[n] );
	printf( "AIN %d = %d (%.2f V)\n", n+1, out_arr[n], dv );
      }
    }
  } else if ( ! strcmp( vlist->sValue, "din" ) ) {
    // read digital input
    if ( vlist->next ) {
      if ( vlist->next->iValue < 1 || vlist->next->iValue > 8 ) {
	fprintf( stderr, "*** error: invalid channel number '%d'\n", vlist->next->iValue );
	return -1;
      } else {
	printf( "DIN %d = %d\n", vlist->next->iValue, 
		k8061_ReadDigitalChannel( cmd8061_card, vlist->next->iValue) );
      }
    } else {
      k8061_ReadAllDigital( cmd8061_card, out_arr );
      for ( n=0;n<8;n++)
	printf( "DIN %d = %d\n", n+1, out_arr[n] );
    }
  } else {
    fprintf( stderr, "*** error: unknown argument '%s' for read back command\n", 
	     vlist->sValue );
    fflush( stderr );
    return -1;
  }


  free_vlist( vlist );
  
  return 0;
}

/* --- wait --- */
int cmd_wait( char *arg ) {

  int usecs = 0;
  double d_usecs = 0.;

  if ( ! arg ) {
    fprintf( stderr, "*** error: keyword 'wait' expects argument\n" );
    return -1;
  }
  stripwhite( arg );
  if ( ! strlen( arg ) ) {
    fprintf( stderr, "*** error: keyword 'wait' expects argument\n" );
    return -1;
  }

  d_usecs = atof( arg );
  printf( "Sleeping %.1f sec...\n", d_usecs );

  usecs = (int) ( 1000000 * d_usecs );
  usleep( usecs );

  return 0;
}


/*-- exec --- */
int cmd_exec( char *arg ) {

  FILE *fp;
  char line[1024];
  int linenr = 0;

  stripwhite( arg );
  fp = fopen( arg, "r" );
  if ( ! fp ) {
    fprintf( stderr, "*** error: no such file '%s'\n", arg );
    return -1;
  }

  while( fgets(line, 1024, fp ) != NULL ) {
    linenr++;
    chomp( line );
    stripwhite( line );
    if ( line[0] == '#' ) continue;
    if ( ! strlen( line ) ) continue;

    cmd_execute( line );
  }    
  fclose( fp );

  return 0;
}


/* --- set jumpers to the board --- */
int cmd_jmps( char *arg ) {

  var_t  *vlist;
  int     n;

  vlist = get_args( arg, &n );
  if ( n != 2 ) {
    fprintf( stderr, "*** error: keyword 'jmp' expects two arguments\n" );
    fflush( stderr );
    return -1;
  }

  if ( ! strcmp( vlist->sValue, "ain" ) ) {
    if ( vlist->next ) {
      k8061_SetADCJumpers( cmd8061_card, vlist->next->hValue );
    } else {
      fprintf( stderr, "*** error: no bitpattern given for ADC jumpers\n" );
      return -1;
    }
  } else if ( ! strcmp( vlist->sValue, "aout" ) ) {
    if ( vlist->next ) {
      k8061_SetDACJumpers( cmd8061_card, vlist->next->hValue );
    } else {
      fprintf( stderr, "*** error: no bitpattern given for DAC jumpers\n" );
      return -1;
    }
  } else {
    fprintf( stderr, "*** error: invalid group, possible choices are ain/aout\n" );
    return -1;
  }


  return 0;
}
