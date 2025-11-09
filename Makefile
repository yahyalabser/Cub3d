NAME = cub3d
CC = cc
FLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

SRC_PARSE = parsing/parse.c parsing/utils_str.c parsing/free_utils.c \
			parsing/map.c parsing/parse_color.c parsing/parse_line.c \

SRC = main.c \
	$(SRC_PARSE) \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c 


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o: %.c cub3d.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
