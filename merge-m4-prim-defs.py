import os
import re
from pathlib import Path
from pprint import pprint

ps = {}
for d, sd, fs in os.walk('primitive'):
    for f in fs:
        if f.endswith('.m4'):
            ps[f[:-3]] = d.split('/', 1)[1]

cs = {}
for d, sd, fs in os.walk('compiled'):
    for f in fs:
        if f.endswith('.c'):
            cs[f[:-2]] = d.split('/', 1)[1]

for n, d in cs.items():
    if n not in ps:
        continue

    txt = open(Path('.') / 'compiled' / d / (n + '.c')).read()
    if ('_define_primitive(' not in txt
        and '_define_primitive_ext(' not in txt
        and '_define_parsing_primitive(' not in txt
        and '_define_immediate_primitive(' not in txt):
        continue

    txt = re.sub(r'^_define_primitive\(', 'define_primitive(', txt)
    txt = re.sub(r'^_define_primitive_ext\(', 'define_primitive_ext(', txt)
    txt = re.sub(r'^_define_parsing_primitive\(', 'define_parsing_primitive(', txt)
    txt = re.sub(r'^_define_immediate_primitive\(', 'define_immediate_primitive(', txt)

    with open(Path('.') / 'primitive' / ps[n] / (n + '.m4'), 'a') as f:
        f.write(txt)
