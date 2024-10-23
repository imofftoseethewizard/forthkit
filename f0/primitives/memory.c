void _add_store_byte(number n)
{
    *(byte *)_to_ptr(*sp) += (byte)n;
}

void _add_store_cell(number n)
{
    *_to_ptr(*sp) += n;
}

void _add_store_mixed_double_number(number n)
{
    *(double_number *)_to_ptr(*sp) += n;
}

primitive add_store_byte()
{
    _add_store_byte(*(sp+1));
    sp += 2;
}

primitive add_store_byte_op()
{
    _add_store_byte(*ip++);
    sp++;
}

primitive append_byte()
{
    *dp++ = (byte)*sp++;
    _check_dictionary_bounds();
}

primitive fetch_byte()
{
    *sp = *(byte *)_to_ptr(*sp);
}

primitive pop_byte()
{
    *--sp = (cell)*--dp;
}

primitive store_byte()
{
    *(byte *)_to_ptr(*sp) = (byte)*(sp+1);
    sp += 2;
}

primitive add_store_cell()
{
    _add_store_cell(*(sp+1));
    sp += 2;
}

primitive add_store_cell_op()
{
    _add_store_cell(*ip++);
    sp++;
}

primitive append_cell()
{
    *(cell *)dp = *sp++;
    dp += sizeof(cell);
    _check_dictionary_bounds();
}

primitive fetch_cell()
{
    *sp = *_to_ptr(*sp);
}

primitive pop_cell()
{
    dp -= sizeof(cell);
    *--sp = *(cell *)dp;
}

primitive store_cell()
{
    *_to_ptr(*sp) = *(sp+1);
    sp += 2;
}

primitive add_store_mixed_double_number()
{
    _add_store_mixed_double_number(*(sp+1));
    sp += 2;
}

primitive add_store_mixed_double_number_op()
{
    _add_store_mixed_double_number(*ip++);
    sp++;
}

primitive append_double_cell()
{
    *(cell *)dp = *sp++;
    dp += sizeof(cell);

    *(cell *)dp = *sp++;
    dp += sizeof(cell);

    _check_dictionary_bounds();
}

primitive fetch_double_cell()
{
    *(sp-1) = *_to_ptr(*sp);
    *sp = *(_to_ptr(*sp)+1);
    sp--;
}

primitive pop_double_cell()
{
    dp -= sizeof(cell);
    *--sp = *(cell *)dp;

    dp -= sizeof(cell);
    *--sp = *(cell *)dp;
}

primitive store_double_cell()
{
    *_to_ptr(*sp) = *(sp+1);
    *(_to_ptr(*sp)+1) = *(sp+2);
    sp += 3;
}
