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

// typedef struct s_img
// {
// 	void	*img;
// 	char	*addr;
// 	int		bpp;
// 	int		line_len;
// 	int		endian;
// }	t_img;

// typedef struct s_player
// {
// 	double	x;
// 	double	y;
// 	double	angle;
// 	double	fov;
// }	t_player;

// typedef struct s_ray
// {
// 	double	angle;   // angle du rayon
// 	double	dir_x;   // cos(angle)
// 	double	dir_y;   // sin(angle)

// 	// DDA
// 	int		map_x;
// 	int		map_y;
// 	double	side_dist_x;
// 	double	side_dist_y;
// 	double	delta_dist_x;
// 	double	delta_dist_y;
// 	int		step_x;
// 	int		step_y;
// 	int		side;
// 	double	perp_dist;
// }	t_ray;

// typedef struct s_game
// {
// 	void		*mlx;
// 	void		*win;
// 	t_img		img;
// 	t_config	config;
// 	t_player	player;
// 	double		proj_plane_dist;
// }	t_game;


# define TILE            64
# define WIDTH           1200
# define HEIGHT          800
# define FOV             1.0471975512 /* 60 deg in rad */
# define NUM_RAYS        WIDTH
# define WALL_STRIP      1
# define EPS             1e-6
# define COLLISION_BUF   6.0

/* macOS keycodes; adjust if Linux (X11) */
# define KEY_ESC   53
# define KEY_A     0
# define KEY_S     1
# define KEY_D     2
# define KEY_W     13
# define KEY_LEFT  123
# define KEY_RIGHT 124

/* ======= RUNTIME TYPES ======= */
typedef struct s_img {
	void  *img;
	char  *data;
	int   w;
	int   h;
	int   bpp;
	int   line_len;
	int   endian;
} t_img;

typedef struct s_player {
	double x;
	double y;
	double angle;
	double move_speed;
	double rot_speed;
	int    walk_dir;    /* -1, 0, +1 */
	int    strafe_dir;  /* -1, 0, +1 */
	int    turn_dir;    /* -1, 0, +1 */
} t_player;

typedef struct s_ray {
	double ray_angle;
	double wallhitx;
	double wallhity;
	double distance;
	int    hit_vertical;
	int    ray_up;
	int    ray_down;
	int    ray_left;
	int    ray_right;
} t_ray;

typedef struct s_game {
	/* external parsed config (copied values) */
	char  **map;
	int   map_w;
	int   map_h;
	int   ceil_color;
	int   floor_color;

	/* graphics */
	void  *mlx;
	void  *win;
	t_img frame;

	/* textures */
	t_img tex_n;
	t_img tex_s;
	t_img tex_e;
	t_img tex_w;

	/* player */
	t_player pl;
} t_game;

/* ======= ENGINE API ======= */
/* init & main */
int   game_init_from_config(t_game *g, t_config *cfg);
void  game_shutdown(t_game *g);

/* rendering */
void  render_frame(t_game *g);

/* raycasting core */
t_ray *cast_single_ray(t_game *g, double ray_angle);
t_ray **cast_all_rays(t_game *g);

/* intersections */
void  find_horizontal_hit(t_game *g, t_ray *ray, double *hx, double *hy);
void  find_vertical_hit(t_game *g, t_ray *ray, double *vx, double *vy);

/* utils & math */
double normalize_angle(double a);
int    is_wall_pixel(t_game *g, int x, int y);
int    is_blocked(t_game *g, double x, double y);
int    get_texel(t_img *img, int x, int y);
void   put_px(t_game *g, int x, int y, int color);
void   clear_frame(t_game *g);
double clamp_min(double v, double minv);

/* input loop */
int    on_key_press(int key, t_game *g);
int    on_key_release(int key, t_game *g);
int    on_loop(t_game *g);
int    on_close(t_game *g);

/* helpers */
void   find_player_spawn(t_game *g);
void   load_texture_or_die(t_img *img, void *mlx, const char *path);






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
// void	init_game(t_game *g);
// int		render_frame(t_game *g);
// void	img_pixel_put(t_img *img, int x, int y, int color);
// int		exit_error(char *mssg);

// double	compute_ray_angle(t_game *g, int x);
// void	init_ray_direction(t_ray *ray, t_game *g, int x);
// void	cast_rays(t_game *g);
// void	init_dda(t_ray *ray, t_game *g);
// void	perform_dda(t_ray *ray, t_game *g);
// void	compute_perp_dist(t_ray *ray, t_game *g);



#endif