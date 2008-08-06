#include "k8061.h"

int k8061_OutputAnalogChannelVolt( int iCard, int iChan, double volt ) {
  
  int value;
  unsigned char mask = 0;
  
  _k8061_WriteBuffer[0] = k8061_cmdSetAnalogChannel;
  _k8061_WriteBuffer[1] = iChan - 1;

  mask = 1 << ( iChan - 1 );
  if ( ( _k8061_jmp_dac[iCard] & mask ) == mask ) {
    value = (int) ( 255 * volt / 10. );
  } else {
    value = (int) ( 255 * volt / 5. );
  }
  
  if ( value < 0 ) {
    _k8061_WriteBuffer[2] = 0;
    fprintf( stderr, "+++ warning <%d::AOUT%d> %.2f V is too low, set DAC to 0\n",
	     iCard, iChan, volt );
  } else if ( value > 255 ) {
    _k8061_WriteBuffer[2] = 255;
    fprintf( stderr, "+++ warning <%d::AOUT%d>: %.2f V is too high, set DAC to 255\n", 
	     iCard, iChan, volt );
  } else {

    _k8061_WriteBuffer[2] = value;

  }
  
  return k8061_ExecIO( iCard, 3, 4 );
}
