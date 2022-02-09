if __name__ == '__main__':

    import sys
    print(sys.argv[-1])
    lines = open(sys.argv[-1]).readlines()
    f = open(sys.argv[-1], 'w')
    ready = False
    strip_chars = " \n:"
    for line in lines:
        if ready:
            print(f'_primitive({line.strip(strip_chars)}) {{', file=f)
            ready = False
        elif line.startswith('if (0) {'):
            ready = True
        else:
            print(line, end='', file=f)
