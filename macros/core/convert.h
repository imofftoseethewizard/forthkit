#define _parse_digit(c) \
        '0' <= c && c <= '9' ? (c - '0') \
      : 'A' <= c && c <= 'Z' ? (c - 'A' + 10) \
      : 'a' <= c && c <= 'z' ? (c - 'a' + 10) \
      : -1
