__primitive(pr_num_s)  
{
    register length_type *idx = (length_type *)here;
    *idx = _c_number_pad_size;
}
__end
__define_primitive("<#", pr_num_s);
