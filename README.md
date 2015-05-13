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
  into the file using the library, and,when building an application, link with <br><code>-LLIBDIR -Wl,-rpath -Wl,LIBDIR -larray</code><br> where <code>LIBDIR</code> is the location of the installed library (which is usually <code>/usr/local/lib</code> for the library and <code>/usr/local/include</code> for the header).<br>
  Details can be found about linking in the output of <code>sudo make install</code> when you install it
# Compiling
  Once in the repository, the <code>autogen.sh</code> script will 
automate the autotools to produce the familiar process <code>./configure 
&& make && sudo make install</code> which will most likely install to 
<code>/usr/local/</code>
# Have fun!
