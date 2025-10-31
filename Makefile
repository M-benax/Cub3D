
NAME    = cub3D
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g -I./includes

SRCS    = src/get_next_line_utils.c src/get_next_line.c src/helpers.c src/main.c \
          src/parser_color.c src/parser_ident01.c src/parser_ident02.c src/parser_main.c \
          src/utils_free.c src/utils_grid.c src/utils_io.c src/validate.c
OBJS    = $(SRCS:.c=.o)


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