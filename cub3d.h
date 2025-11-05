#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include "get_next_line/get_next_line.h"
# include <math.h>
# include "mlx.h"


# define WIDTH      800
# define HEIGHT     600
# define FOV_RAD    (60.0 * M_PI / 180.0)
# define MOVE_SPEED 0.08
# define ROT_SPEED  0.05

typedef struct	s_str
{
	char			*content;
	struct s_str	*next;
}t_str;

typedef struct s_config 
{
   char  *no_texture;
   char  *so_texture;
   char *we_texture;
   char *ea_texture;
   int floor_color;
   int ceiling_color;
   t_str *map;
   char **map_array; // sous form d une array
   int map_width;
   int map_height; 
} t_config;

/*--------------------------*/

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
	double	fov;
}	t_player;

typedef struct s_ray
{
	double	angle;   // angle du rayon
	double	dir_x;   // cos(angle)
	double	dir_y;   // sin(angle)

	// DDA
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_dist;
}	t_ray;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_config	config;
	t_player	player;
	double		proj_plane_dist;
}	t_game;






/*---------------------- PARSING -----------------------*/
int		parse_file(char *file, t_config *config);
int		parse_identifier(char *line, int i, t_config *config);
int		parse_color(char *line);
int		ft_strlen(char *s);
int  	ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strdup(char *src);
void	*ft_memcpy(char *dst, char *src, size_t n);
void	*ft_memset(char *b, int c, size_t len);
int		exit_error(char *mssg);
void	free_array(char **arr);
void	free_map(t_str *map);
void	free_config(t_config *config);
void	free_all(t_config *config);
int		validate_map(t_config *config);
int		is_map_line(char *line);
/*---------------------- recasting -----------------------*/
void	init_game(t_game *g);
int		render_frame(t_game *g);
void	img_pixel_put(t_img *img, int x, int y, int color);
int		exit_error(char *mssg);

double	compute_ray_angle(t_game *g, int x);
void	init_ray_direction(t_ray *ray, t_game *g, int x);
void	cast_rays(t_game *g);
void	init_dda(t_ray *ray, t_game *g);
void	perform_dda(t_ray *ray, t_game *g);
void	compute_perp_dist(t_ray *ray, t_game *g);



#endif