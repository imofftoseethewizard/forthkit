
/* Aliases for some temporary variables to provide readability. */

__primitive(pr_parse)  
{

    register char delimiter = *sp++;
    register int len = 0;

    *--sp = (cell)&source[point];

    while (point < source_len && source[point] != delimiter)
        len++, point++;

    *--sp = len;

}
__end
__define_primitive("PARSE", pr_parse);
