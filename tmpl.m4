include(model.m4)dnl

begin_primitives
include_primitive(`t.pr.c')dnl
include_primitive(`s.pr.c')dnl
end_primitives

before define macros
define_macros()

before declare primitives
declare_primitives()

before implement primitives
implement_primitives()
done
