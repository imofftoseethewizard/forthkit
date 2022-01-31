if __name__ == '__main__':

    import sys
    print(sys.argv[-1])
    lines = open(sys.argv[-1]).readlines()
    f = open(sys.argv[-1], 'w')
    held = None
    for line in lines:
        if held:
            print(line, end='', file=f)
        elif line.split('(', 1)[0] in ('define_primitive', 'define_immediate_primitive', 'define_parsing_primitive'):
            held = line
        else:
            print(line, end='', file=f)

    print(held, end='', file=f)
