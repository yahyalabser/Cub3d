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
   // Chemins des textures
   char *no_texture; // Nord
   char *so_texture; // Sud
   char *we_texture; // Ouest
   char *ea_texture; // Est

   // Couleurs sol et plafond (format RGB, généralement 0xRRGGBB)
   int floor_color;
   int ceiling_color;

   // Map 2D (tableau de chaînes)
   t_str *map;
} t_config;

//parse
int parse_file(char *file, t_config *config);
void	parse_line(char *line, t_config *config, int *map_started);
int	ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *src);

// utils str
int	ft_strlen(char *s);
int ft_strcmp(char *s1, char *s2);
void	*ft_memset(char *b, int c, size_t len);
void	*ft_memcpy(char *dst, char *src, size_t n);

// error
int exit_error(char *mssg);

// free
void	free_array(char **arr);
void	free_map(t_str *map);
void	free_config(t_config *config);
void	free_all(t_config *config);

// map 
int	validate_map(t_str *map);
int	is_map_line(const char *line);

#endif