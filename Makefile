SRC = render/main.c render/utils.c render/events.c render/player_mov.c \
      render/dda_ray_cast.c render/render.c render/init_game.c \
      parse/get_next_line.c parse/get_next_line_utils.c parse/helpers.c \
      parse/helpers02.c parse/parser_color.c parse/parser_ident01.c \
      parse/parser_ident02.c parse/parser_main.c parse/utils_free.c \
      parse/utils_grid.c parse/utils_io.c parse/validate.c \
      parse/validate_helper.c
LIBS = -lmlx -framework OpenGL -framework AppKit
FLAGS = -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)
NAME = cub3D

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c includes/cub3d.h includes/parse.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
