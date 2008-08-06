#include "k8061.h"

int k8061_OutputPWM( int iCard, int value ) {
  
  // check the value
  if ( value < 0 ) value = 0;
  if ( value > 1023 ) value = 1023;
 
  _k8061_WriteBuffer[0] = k8061_cmdOutputPWM;

  /*
    The following piece of code was translated from the inline asembler code
    in the DLL source code ( K8061.PAS ) :
    asm
      mov eax,k    ; k is the value
      and al,03h   ; al are the lower 8 bits of eax
      mov lo,al    ; lo is the low part, which should go in send_buf[1]
      mov eax,k    
      shr eax,2    ; right-shift eax register by 2
      mov hi,al    ; hi is the high part, which should go in send_buf[2]
    end;
  */

  _k8061_WriteBuffer[1] = (unsigned char) ( value & 0x03 );
  _k8061_WriteBuffer[2] = (unsigned char) ( value >> 2 ) & 0xFF;
  
  return k8061_ExecIO( iCard, 3, 4 );
}
