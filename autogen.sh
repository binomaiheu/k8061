#!/bin/sh

echo "Bootstrapping source tree..."

# running aclocal
aclocal -I m4 \
    || { echo "aclocal failed..."; exit 1; }

# running autoconf
autoconf --force -I m4 \
    || { echo "autoconf failed..."; exit 1; }

# running libtoolize
if [ `uname` == "Darwin" ]; then
    glibtoolize --copy --force \
	|| { echo "libtoolize failed..."; exit 1; }
else
    libtoolize  --copy --force \
	|| { echo "libtoolize failed..."; exit 1; }
fi

# running automake
automake --gnu --copy --add-missing \
    || { echo "automake failed..."; exit 1; }


echo "Bootstrap successfully completed."
echo "Now run ./configure and then make; make install to configure and build."
