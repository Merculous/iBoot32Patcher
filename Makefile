
CC=clang
CFLAGS=-Wno-multichar -Wno-int-conversion src/*.c
CPPFLAGS=-I.
NAME=iBoot32Patcher

all:
	$(CC) $(CPPFLAGS) $(CFLAGS) -o $(NAME)
clean:
	rm -f iBoot32Patcher
