
SRCS=$(wildcard *.c)
CFLAGS=-ggdb -lcunit
.PHONY: all
all: unittests

unittests: $(SRCS)
	$(CC) -o $@ $(SRCS) $(CFLAGS) 
