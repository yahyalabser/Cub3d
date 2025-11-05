#include "../cub3d.h"

static void	find_player_start(t_game *g)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < g->config.map_height)
	{
		x = 0;
		while (x < g->config.map_width)
		{
			c = g->config.map_array[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				g->player.x = x + 0.5;
				g->player.y = y + 0.5;
				if (c == 'N')
					g->player.angle = 3 * M_PI / 2;
				else if (c == 'S')
					g->player.angle = M_PI / 2;
				else if (c == 'W')
					g->player.angle = M_PI;
				else
					g->player.angle = 0;
				g->config.map_array[y][x] = '0'; 
				return ;
			}
			x++;
		}
		y++;
	}
	exit_error("Error:\nNo player position in map.\n");
}

static void	init_image(t_game *g)
{
	g->img.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->img.img)
		exit_error("Error:\nmlx_new_image failed.\n");
	g->img.addr = mlx_get_data_addr(
			g->img.img, &g->img.bpp, &g->img.line_len, &g->img.endian);
	if (!g->img.addr)
		exit_error("Error:\nmlx_get_data_addr failed.\n");
}

void	init_game(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		exit_error("Error:\nmlx_init failed.\n");
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "cub3D");
	if (!g->win)
		exit_error("Error:\nmlx_new_window failed.\n");
	init_image(g);
	find_player_start(g);
	g->player.fov = FOV_RAD;
	g->proj_plane_dist = (WIDTH / 2.0) / tan(g->player.fov / 2.0);
}

void	img_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

static void	clear_background(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				img_pixel_put(&g->img, x, y, g->config.ceiling_color);
			else
				img_pixel_put(&g->img, x, y, g->config.floor_color);
			x++;
		}
		y++;
	}
}


int	render_frame(t_game *g)
{
	clear_background(g);
	// mwn b3ed o netal9 ray
	mlx_put_image_to_window(g->mlx, g->win, g->img.img, 0, 0);
	return (0);
}
