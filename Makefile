NAME  = cub3d
CC    = cc
FLAGS = -Wall -Wextra -Werror -g3  # -fsanitize=address

MLX = -lmlx
APPKIT = -framework AppKit
OPENGL = -framework OpenGL

PARSING_SRCS = \
	parsing/parse.c \
	parsing/utils_str.c \
	parsing/free_utils.c \
	parsing/map.c \
	parsing/parse_color.c \
	parsing/parse_line.c

RAYCASTING_SRCS = \
	raycasting/raycasting_utils.c \
	raycasting/raycasting_utils1.c

SRCS = \
	main.c \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c \
	$(PARSING_SRCS) \
	$(RAYCASTING_SRCS)


OBJ = $(SRCS:.c=.o)

HEADERS = cub3d.h get_next_line/get_next_line.h

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(MLX) $(APPKIT) $(OPENGL) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
