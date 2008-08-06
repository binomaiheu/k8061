bin_PROGRAMS = cmd8061

cmd8061_SOURCES = cmd8061.c cmd_argparser.c cmd_cleanup.c cmd_commands.c \
                  cmd_completion.c cmd_execute.c cmd_init.c cmd_strmanip.c \
                  cmd8061.h cmd_argparser.h

cmd8061_LDADD = @top_srcdir@/libK8061/libK8061.la $(libusb_LIBS) $(readline_LIBS)
INCLUDES      = -I@top_srcdir@/libK8061 $(libusb_CFLAGS) 


