
NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./minilibx-linux

SRCS = src/main.c \
	   src/init.c \
	   src/parser.c \
	   src/textures.c \
	   src/utils.c \
	   src/events.c \
	   src/helpers.c \
	   src/get_next_line.c \
	   src/validate.c

OBJS = $(SRCS:.c=.o)

MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

all: $(MLX_LIB) $(NAME)

$(MLX_LIB):
	@echo "Building MinilibX in $(MLX_DIR)..."
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(MLX_DIR) clean || true

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(MLX_DIR) fclean || true
	@rm -f $(MLX_LIB)

re: fclean all

.PHONY: all clean fclean re