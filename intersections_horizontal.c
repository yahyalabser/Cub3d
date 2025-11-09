#include "cub3d.h"

static int nearly_horizontal(double ang) 
{ 
    return fabs(sin(ang)) < EPS;
}

static int check_y_for_wall(int ray_up, double y)
{
	return ray_up ? ((int)y - 1) : (int)y;
}

void find_horizontal_hit(t_game *g, t_ray *ray, double *hx, double *hy)
{
	*hx = INT_MAX;
	*hy = INT_MAX;
	if (nearly_horizontal(ray->ray_angle))
		return;

	double tan_a = tan(ray->ray_angle);

	double yint = floor(g->pl.y / TILE) * TILE;
	if (ray->ray_down) yint += TILE;
	double xint = g->pl.x + (yint - g->pl.y) / tan_a;

	double ystep = ray->ray_down ? TILE : -TILE;
	double xstep = TILE / tan_a;
	if ((ray->ray_left && xstep > 0) || (ray->ray_right && xstep < 0))
		xstep = -xstep;

	double nx = xint;
	double ny = yint;

	while (nx >= 0 && nx <= g->map_w * TILE && ny >= 0 && ny <= g->map_h * TILE)
	{
		int cy = check_y_for_wall(ray->ray_up, ny);
		if (is_wall_pixel(g, (int)nx, cy))
		{
			*hx = nx; *hy = ny;
			return;
		}
		nx += xstep;
		ny += ystep;
	}
}