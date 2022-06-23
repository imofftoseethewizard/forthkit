/* EMIT ( char -- )

   Transmit character to the current output device.
 */
#define _emit() putc(*sp++, stdout)

__primitive(pr_emit)
{
    /* EMIT ( char -- )

       Transmit character to the current output device.
     */

    _emit();
}
__end
__define_primitive("EMIT", pr_emit);
