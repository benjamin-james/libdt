# array
A dynamic array library for general purpose.
# Prerequisites
  Must have a C compiler installed (i.e. <code>gcc</code>)<br>
  Must have GNU Autotools installed (i.e. <code>autoconf</code>, <code>automake</code>, <code>libtool</code>)
# Summary
  Uses the <code>array</code> structure to hold data. 
  Must be initialized by <code>array_create</code>
  and must be destroyed by <code>array_destroy</code>
  Note: it does not copy the data, it merely references it. So, stack-allocated data would not work well (at least at the moment !)
# Use
  To use the library, simply type
  <br><code>#include "array.h"</code><br>
  into the file using the functions, and link with <br><code>-LLIBDIR -Wl,-rpath -Wl,LIBDIR -larray</code><br> where <code>LIBDIR</code> is the location of the installed library (which is usually <code>/usr/local/lib</code> for the library and <code>/usr/local/include</code> for the header).<br>
  Details can be found about linking in the output of <code>sudo make install</code> when you install it
# Compiling
  Once in the repository, type these commands in order:
  <br><code>autoconf</code>, <code>libtoolize</code>, <code>aclocal</code>, <code>autoheader</code>, <code>automake --add-missing</code>, <code>autoreconf</code><br> to configure, then the infamous <br><code>./configure && make && sudo make install</code><br> to compile and install the library
# Have fun!
