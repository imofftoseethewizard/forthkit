#! /usr/bin/env python3

import re

from collections import namedtuple

ErrorData = namedtuple('ErrorData', ('id', 'symbol', 'desc'))

def generate_errors_h(error_data):

    error_codes = '\n'.join([f'    {e.symbol} = {e.id},' for e in error_data])

    return fill_template('errors.tmpl.h', { 'error_code_definitions': error_codes })

def generate_errors_c(error_data):

    error_descs = '\n'.join([
        f'''    {{
        {e.symbol},
        "{e.symbol}",
        "{e.desc}"
    }},
'''
        for e in error_data
    ])

    return fill_template('errors.tmpl.c', { 'error_descriptor_initializers': error_descs })

def parse_errors_md():

    lines = open('errors.md').readlines()

    data_lines = [l for l in lines if l.startswith('    ')]

    return [ErrorData(*re.split(' +', l.strip(), 2)) for l in data_lines]

def fill_template(path, values):

    tmpl = open(path).read()

    result = tmpl

    for k, v in values.items():

        pattern = '/*{ ' + k + ' }*/'
        result = result.replace(pattern, v)

    return result

if __name__ == '__main__':

    error_data = parse_errors_md()

    print(generate_errors_h(error_data))
    print(generate_errors_c(error_data))
