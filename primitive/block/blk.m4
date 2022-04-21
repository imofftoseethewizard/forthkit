__primitive(pr_blk)  
{
    *--sp = _from_ptr(&e[ea_blk]);
}
__end
__define_primitive("BLK", pr_blk);
