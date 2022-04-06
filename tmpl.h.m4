include(model.m4)

begin_primitives()
include_primitive(`t.pr.c')
include_primitive(`s.pr.c')
end_primitives()

define_macros()

declare_primitives()
ignore_implementations()
