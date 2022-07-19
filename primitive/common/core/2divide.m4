__primitive(pr_2divide)
{
    *(number *)sp /= 2;
}
__end
__define_primitive("2/", pr_2divide);
