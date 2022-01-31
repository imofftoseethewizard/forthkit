if __name__ == '__main__':
    import re
    import sys
    from pprint import pprint

    symbols = {}
    for line in sys.stdin.readlines():
        if line.startswith('defining ') or line.startswith('operator '):
            _, key, value = re.split(' +', line.strip())
            symbols[key] = value
        else:
            for key, value in symbols.items():
                try:
                    line = re.sub(re.escape(value), key, line)
                except:
                    print(key, value, line)
                    raise
            print(line, end='')

    pprint(symbols)
