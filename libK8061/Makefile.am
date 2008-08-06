lib_LTLIBRARIES = libK8061.la

libK8061_la_SOURCES = k8061.h k8061_CheckOpen.c k8061_ClearAllAnalog.c k8061_ClearAllDigital.c \
                      k8061_ClearAnalogChannel.c k8061_ClearDigitalChannel.c k8061_CloseDevices.c \
                      k8061_ExecIO.c k8061_GetDeviceCount.c k8061_Globals.c k8061_HasPower.c \
                      k8061_Init.c k8061_IsConnected.c k8061_ListDevices.c k8061_OpenDevices.c \
                      k8061_OutputAllAnalog.c k8061_OutputAllDigital.c k8061_OutputAnalogChannel.c \
                      k8061_OutputPWM.c k8061_ReadAllAnalog.c k8061_ReadAllDigitalByte.c \
                      k8061_ReadAnalogChannel.c k8061_ReadBackAnalogOut.c k8061_ReadAllDigital.c \
                      k8061_ReadBackDigitalOut.c k8061_ReadBackPWMOut.c k8061_ReadCounters.c \
                      k8061_ReadDigitalChannel.c k8061_ReadVersion.c k8061_ResetCounters.c \
                      k8061_ScanBus.c k8061_SetAllAnalog.c k8061_SetAllDigital.c \
                      k8061_SetAnalogChannel.c k8061_SetDigitalChannel.c k8061_WriteStatus.c \
                      k8061_GetVoltValue.c k8061_WriteJumpers.c  k8061_OutputAnalogChannelVolt.c \
                      k8061_OutputAllAnalogVolt.c


libK8061_la_LDFLAGS= -version-info $(LIBK8061_VERSION) -release $(LIBK8061_RELEASE)

library_includedir=$(includedir)
library_include_HEADERS = k8061.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libK8061.pc
