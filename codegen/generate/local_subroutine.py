def primitive_implementation(p):

    return f'void {p.symbol}(void) {p.body.strip()}\n'

def primitive_declarations(primitives):

    return '\n'.join([f'auto void {p.symbol}(void);' for p in primitives])
