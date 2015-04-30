# array
A dynamic array library for general purpose.
# Summary
  Uses the <code>array</code> structure to hold data. 
  Must be initialized by <code>array_create</code>
  and must be destroyed by <code>array_destroy</code>
  Note: it does not copy the data, it merely references it.
# Use
  To use the library, simply type
  <br><code>#include "array.h"</code><br>
  into the file using the functions, and link with <code>-LLIBDIR -Wl,-rpath -Wl,LIBDIR</code> where LIBDIR is the location of the installed library.
  Details can be found about linking in the output of <code>sudo make install</code> when you install it
# Compiling
  Type <code>autoconf && libtoolize && aclocal && automake --add-missing && autoreconf && ./configure && make && sudo make install</code> to install the array
# Have fun!
