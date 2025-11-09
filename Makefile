# NAME  = cub3d
# CC    = cc
# FLAGS = -Wall -Wextra -Werror -g3  # -fsanitize=address

# MLX = -lmlx
# APPKIT = -framework AppKit
# OPENGL = -framework OpenGL

# PARSING_SRCS = \
# 	parsing/parse.c \
# 	parsing/utils_str.c \
# 	parsing/free_utils.c \
# 	parsing/map.c \
# 	parsing/parse_color.c \
# 	parsing/parse_line.c

# # RAYCASTING_SRCS = \
# # 	raycasting/raycasting_utils.c \
# # 	raycasting/raycasting_utils1.c

# RAYCASTING_SRCS = \
# 	cast.c hooks.c \
# 	intersections_horizontal.c \
# 	intersections_vertical.c \
# 	rendre.c utils.c \


# SRCS = \
# 	main.c \
# 	get_next_line/get_next_line.c \
# 	get_next_line/get_next_line_utils.c \
# 	$(PARSING_SRCS) \
# 	$(RAYCASTING_SRCS)


# OBJ = $(SRCS:.c=.o)

# HEADERS = cub3d.h get_next_line/get_next_line.h

# all: $(NAME)

# $(NAME): $(OBJ)
# 	$(CC) $(FLAGS) $(OBJ) $(MLX) $(APPKIT) $(OPENGL) -o $(NAME)

# %.o: %.c $(HEADERS)
# 	$(CC) $(FLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJ)

# fclean: clean
# 	rm -f $(NAME)

# re: fclean all

# .PHONY: all clean fclean re
# ==============================
#  Makefile Cub3D - Version Linux
# ==============================

NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
# Pour activer l'address sanitizer (décommenter la ligne suivante)
# CFLAGS     += -fsanitize=address

# Répertoire où se trouve la MinilibX (adapter si nécessaire)
MLX_DIR     = ./mlx

# Includes supplémentaires (adapter si tu as des headers dans mlx/)
INCLUDES    = -I . -I $(MLX_DIR)

# Librairies MinilibX Linux:
#   -lmlx       : la lib MinilibX
#   -lXext -lX11: extensions X11
#   -lm         : math
#   -lz         : compression (souvent requis par certaines versions)
MLX_LIBS    = -L $(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# ==============================
# Sources parsing
# ==============================
PARSING_SRCS = \
	parsing/parse.c \
	parsing/utils_str.c \
	parsing/free_utils.c \
	parsing/map.c \
	parsing/parse_color.c \
	parsing/parse_line.c

# ==============================
# Sources raycasting
# ==============================
RAYCASTING_SRCS = \
	cast.c \
	hooks.c \
	intersections_horizontal.c \
	intersections_vertical.c \
	rendre.c \
	utils.c

# ==============================
# Autres sources (get_next_line etc.)
# ==============================
GNL_SRCS = \
	get_next_line/get_next_line.c \
	get_next_line/get_next_line_utils.c

SRCS = \
	main.c \
	$(GNL_SRCS) \
	$(PARSING_SRCS) \
	$(RAYCASTING_SRCS)

OBJS = $(SRCS:.c=.o)

HEADERS = cub3d.h get_next_line/get_next_line.h

# ==============================
# Règles
# ==============================
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) $(MLX_LIBS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Optionnel: cible pour debugger (ajoute -fsanitize et -O0)
debug: CFLAGS += -O0 -fsanitize=address
debug: re

.PHONY: all clean fclean re debug