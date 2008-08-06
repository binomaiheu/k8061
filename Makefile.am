ACLOCAL_AMFLAGS = -I m4

SUBDIRS = libK8061 src

include aminclude.am

MOSTLYCLEANFILES = $(DX_CLEANFILES)


EXTRA_DIST = autogen.sh \
             src/Makefile.simple libK8061/Makefile.simple \
             $(DX_CONFIG) $(DX_DOCDIR) \
             test/dout-runoff.k8061

#add hook for inclusing of doxygen doc in make dist
$(DX_DOCDIR): doxygen-run

