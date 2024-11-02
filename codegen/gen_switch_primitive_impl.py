#! /usr/bin/env python3

import re
import sys

from collections import namedtuple
import generate.computed_goto
import generate.local_subroutine
import generate.switch

Primitive = namedtuple('Primitive', ('symbol', 'body'))

def fill_template(path, values):

    tmpl = open(path).read()

    result = tmpl

    for k, v in values.items():

        pattern = '/*{ ' + k + ' }*/'
        result = result.replace(pattern, v)

    return result

def generate_primitive_implementations(primitives, generate_primitive_implementation):

    impls = [generate_primitive_implementation(p) for p in primitives]

    return '\n'.join(impls)

def parse_primitive(text):

    m = re.search(r'^([a-z_0-9]+):[\s]*(.*)', text, re.DOTALL)

    assert m
    return Primitive(*m.groups())

if __name__ == '__main__':

    paths = sys.argv[1:]
    primitives = [parse_primitive(open(p).read()) for p in paths]

    print(generate_primitive_implementations(primitives, generate.computed_goto.primitive_implementation))
    print(generate.computed_goto.primitive_declarations(primitives))
