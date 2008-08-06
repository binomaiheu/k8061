#include "k8061.h"

int k8061_ResetCounters( int iCard ) {
  
  _k8061_WriteBuffer[0] = k8061_cmdResetCounters;

  return k8061_ExecIO( iCard, 1, 2 );
}
