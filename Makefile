.POSIX:

OBJ0 = $(SRC0:.c=.o)
OBJ1 = $(SRC1:.c=.o)
CFLAGS := $(CFLAGS) -ggdb

all: s0 s1

%.o: %.c
	$(CC) -c $(CFLAGS) -c $<

machine1.o: machine1.h ops.c p1.c log.h

main1.o: machine1.h

$(OBJ0) $(OBJ1): config.h

clean:
	rm -f s0 s1 $(OBJ0) $(OBJ1)

s0: $(OBJ0)
	$(CC) -o $@ $(OBJ0) $(LDFLAGS)

s1: $(OBJ1)
	$(CC) -o $@ $(OBJ1) $(LDFLAGS)

.PHONY: all clean
