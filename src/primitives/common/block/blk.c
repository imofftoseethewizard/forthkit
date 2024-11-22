/*|

`BLK ( -- addr )`

The address of a variable containing the number of the mass storage
block being interpreted as the input stream.  If the value of BLK is
zero the input stream is taken from the text input buffer.

  |*/

// BLK
pr_blk:
{
    *--sp = _from_ptr(&e[ea_blk]);
}
