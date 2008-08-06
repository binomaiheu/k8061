#include "k8061.h"

// ----------------------------------------------------------------------------------------
// Get the ADC value in volts
double k8061_GetADCVolt( int iCard, int chan, int val ) {

  unsigned char mask = 0x0;
  double dv = 0.;

  if ( iCard < 0 || iCard > 7 ) {
    fprintf( stderr, "*** error <k8061_GetADCVolt> : Invalid card number %d", iCard );
    fflush( stderr );
    return -1.;
  }

  if ( chan < 1 || chan > 8 ) {
    fprintf( stderr, "*** error <k8061_GetADCVolt> : Invalid channel number %d", chan );
    fflush( stderr );
    return -1.;
  }

  if ( val < 0 || val > 255 ) {
    fprintf( stderr, "*** error <k8061_GetADCVolt> : Invalid ADC value r %d", val );
    fflush( stderr );
    return -1.;
  }

  mask = 1 << ( chan - 1 );
  // if ADC jumper is set, value is from 0 to 5 V, if not from 0 to 10 V.
  // with 10 - bit resolution

  if ( ( _k8061_jmp_adc[iCard] & mask ) == mask ) {
    dv = 5. / 1023.* (double) val;
  } else {
    dv = 10. / 1024. * (double) val;
  }

  return dv;
}


// ----------------------------------------------------------------------------------------
// Get the DAC value in volts
double k8061_GetDACVolt( int iCard, int chan, int val ) {

  unsigned char mask = 0x0;
  double dv = 0.;

  if ( iCard < 0 || iCard > 7 ) {
    fprintf( stderr, "*** error <k8061_GetDACVolt> : Invalid card number %d", iCard );
    fflush( stderr );
    return -1.;
  }

  if ( chan < 1 || chan > 8 ) {
    fprintf( stderr, "*** error <k8061_GetDACVolt> : Invalid channel number %d", chan );
    fflush( stderr );
    return -1.;
  }

  if ( val < 0 || val > 255 ) {
    fprintf( stderr, "*** error <k8061_GetDACVolt> : Invalid DAC value r %d", val );
    fflush( stderr );
    return -1.;
  }


  mask = 1 << ( chan - 1 );

  // if ADC jumper is set, value is from 0 to 10 V, if not from 0 to 5 V.
  // with 8 bit resolution

  if ( ( _k8061_jmp_dac[iCard] & mask ) == mask ) {
    dv = 10. / 255. * (double) val;
  } else {
    dv = 5. / 255. * (double) val;
  }
  return dv;
}


// ----------------------------------------------------------------------------------------
int k8061_SetADCJumpers( int iCard, unsigned char b ) {

  if ( iCard < 0 || iCard > 7 ) {
    fprintf( stderr, "*** error <k8061_SetADCJumperst> : Invalid card number %d", iCard );
    fflush( stderr );
    return -1;
  }

  _k8061_jmp_adc[iCard] = b;
  return 0;
}

// ----------------------------------------------------------------------------------------
int k8061_SetDACJumpers( int iCard, unsigned char b ) {

  if ( iCard < 0 || iCard > 7 ) {
    fprintf( stderr, "*** error <k8061_SetDACJumperst> : Invalid card number %d", iCard );
    fflush( stderr );
    return -1;
  }

  _k8061_jmp_dac[iCard] = b;
  return 0;
}
