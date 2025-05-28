CC = clang
CFLAGS = -Wno-multichar -Wno-int-conversion -g
CPPFLAGS = -I.
NAME = iBoot32Patcher
OBJS = src/finders.o src/functions.o src/iBoot32Patcher.o src/patchers.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(OBJS) -o $(NAME)

src/%.o: src/%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(NAME) $(OBJS)
