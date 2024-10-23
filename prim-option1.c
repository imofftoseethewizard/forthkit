typedef primitive void;

primitive dup()
{
    sp++;
    *sp = *(sp+1);
}
