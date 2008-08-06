#include "k8061.h"

int k8061_OutputAllAnalogVolt( int iCard, double volt_arr[] ) {

  int i = 0;
  int value_arr[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  unsigned char mask = 0;


  _k8061_WriteBuffer[0] = k8061_cmdSetAllAnalog;
  for ( i=0; i<8; i++ ) {

    mask = 1 << i;

    if ( ( _k8061_jmp_dac[iCard] & mask ) == mask ) {
      value_arr[i] = (int) ( 255 * volt_arr[i] / 10. );
    } else {
      value_arr[i] = (int) ( 255 * volt_arr[i] / 5. );
    }

    if ( value_arr[i] < 0 ) {
      _k8061_WriteBuffer[i+1] = 0;
      fprintf( stderr, "+++ warning <%d::AOUT%d> %.2f V is too low, set DAC to 0\n",
	       iCard, i+1, volt_arr[i] );
    } else if ( value_arr[i] > 255 ) {
      _k8061_WriteBuffer[i+1] = 255;
      fprintf( stderr, "+++ warning <%d::AOUT%d>: %.2f V is too high, set DAC to 255\n", 
	       iCard, i+1, volt_arr[i] );
    } else {

      _k8061_WriteBuffer[i+1] = value_arr[i];

    }
  }
  
  return k8061_ExecIO( iCard, 9, 2 );
}
