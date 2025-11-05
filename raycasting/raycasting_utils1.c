#include "../cub3d.h"


double	compute_ray_angle(t_game *g, int x)
{
	double	start_angle;
	double	angle_step;
	double	ray_angle;

	start_angle = g->player.angle - (g->player.fov / 2.0);
	angle_step = g->player.fov / (double)WIDTH;
	ray_angle = start_angle + x * angle_step;
	return (ray_angle);
}

void	init_ray_direction(t_ray *ray, t_game *g, int x)
{
	ray->angle = compute_ray_angle(g, x);
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
}

void	init_dda(t_ray *ray, t_game *g)
{
	ray->map_x = (int)g->player.x;
	ray->map_y = (int)g->player.y;
	if (ray->dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (g->player.x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - g->player.x)
			* ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (g->player.y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - g->player.y)
			* ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray, t_game *g)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0; // 0 = mur vertical
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1; // 1 = mur horizontal
		}
		if (ray->map_x < 0 || ray->map_x >= g->config.map_width
			|| ray->map_y < 0 || ray->map_y >= g->config.map_height)
			break ;
		if (g->config.map_array[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

void	compute_perp_dist(t_ray *ray, t_game *g)
{
	double	px;
	double	py;

	px = g->player.x;
	py = g->player.y;
	if (ray->side == 0)
		ray->perp_dist = (ray->map_x - px + (1.0 - ray->step_x) / 2.0)
			/ ray->dir_x;
	else
		ray->perp_dist = (ray->map_y - py + (1.0 - ray->step_y) / 2.0)
			/ ray->dir_y;
	/* éviter division par 0 ou très petites distances */
	if (ray->perp_dist < 0.0001)
		ray->perp_dist = 0.0001;
}

static void	draw_wall_column(t_game *g, t_ray *ray, int x)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		color;

	line_height = (int)(g->proj_plane_dist / ray->perp_dist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	/* couleur de base (gris) */
	color = 0xAAAAAA;
	/* petit shading : murs horizontaux plus sombres */
	if (ray->side == 1)
		color = 0x777777;
	y = draw_start;
	while (y <= draw_end)
	{
		img_pixel_put(&g->img, x, y, color);
		y++;
	}
}

void	cast_rays(t_game *g)
{
    	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
    {
        init_ray_direction(&ray, g, x);
		init_dda(&ray, g);
		perform_dda(&ray, g);
        compute_perp_dist(&ray, g);
        draw_wall_column(g, &ray, x);


        x++;
    }
}