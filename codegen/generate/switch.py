def primitive_implementation(p):

    return f'case {p.symbol}:{p.body.strip()}\nbreak;\n'

def primitive_declarations(primitives):

    primitive_decls = ',\n'.join([p.symbol for p in primitives])

    return f'enum {{\n primitive_start = c_msb,\n{primitive_decls},\nprimitive_count\n}};'
