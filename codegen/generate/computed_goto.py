def primitive_implementation(p):

    return f'{p.symbol}:\n{p.body.strip()}\n_next();\n'

def primitive_declarations(primitives):

    return ''
