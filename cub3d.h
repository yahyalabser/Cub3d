#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h> // printf
# include <fcntl.h>
# include <string.h>
# include "get_next_line/get_next_line.h"

typedef struct	s_str
{
	char			*content;
	struct s_str	*next;
}t_str;

typedef struct s_config
{
   char *no_texture;
   char *so_texture;
   char *we_texture;
   char *ea_texture;
   int floor_color;
   int ceiling_color;
   t_str *map;
   char **map_array;
   int map_width;
   int map_height; 
} t_config;

//parse
int parse_file(char *file, t_config *config);

// parse line 
int	parse_identifier(char *line, int i, t_config *config);

// parse color
int	parse_color(char *line);

// utils str
int	ft_strlen(char *s);
int ft_strcmp(char *s1, char *s2);
int	ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *src);
void	*ft_memcpy(char *dst, char *src, size_t n);
void	*ft_memset(char *b, int c, size_t len);

// error
int exit_error(char *mssg);

// free
void	free_array(char **arr);
void	free_map(t_str *map);
void	free_config(t_config *config);
void	free_all(t_config *config);

// map 
int	validate_map(t_config *config);
int	is_map_line(char *line);

#endif