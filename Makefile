
NAME    = cub3D
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -I./includes

SRCS    = $(wildcard src/*.c)
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all