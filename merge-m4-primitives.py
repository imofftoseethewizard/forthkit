import os
from pathlib import Path
from pprint import pprint

ps = {}
for d, sd, fs in os.walk('primitive'):
    for f in fs:
        if f.endswith('.c'):
            ps[f[:-2]] = d.split('/', 1)[1]

ms = {}
for d, sd, fs in os.walk('macros'):
    for f in fs:
        if f.endswith('.h'):
            ms[f[:-2]] = d.split('/', 1)[1]

rs = {}
for n, d in ps.items():
    t = ms[n] if n in ms and len(d) < len(ms[n]) else d

    dp = Path('.') / 'primitive' / d
    os.makedirs(dp, exist_ok=True)

    with open(dp / (n + '.m4'), 'w') as f:
        if n in ms:
            f.write(open(Path('.') / 'macros' / ms[n] / (n + '.h')).read())
            f.write('\n')
        f.write(open(Path('.') / 'primitive' / d / (n + '.c')).read())
