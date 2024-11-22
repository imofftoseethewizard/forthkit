/* EMIT ( char -- )

   Transmit character to the current output device.
 */
#define _emit() putc(*sp++, stdout)
