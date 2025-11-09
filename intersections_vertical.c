#include "cub3d.h"

static int nearly_vertical(double ang) { return fabs(cos(ang)) < EPS; }

void find_vertical_hit(t_game *g, t_ray *ray, double *vx, double *vy)
{
	*vx = INT_MAX;
	*vy = INT_MAX;
	if (nearly_vertical(ray->ray_angle))
		return;

	double tan_a = tan(ray->ray_angle);

	double xint = floor(g->pl.x / TILE) * TILE;
	if (ray->ray_right) xint += TILE;
	double yint = g->pl.y + (xint - g->pl.x) * tan_a;

	double xstep = ray->ray_right ? TILE : -TILE;
	double ystep = TILE * tan_a;
	if ((ray->ray_up && ystep > 0) || (ray->ray_down && ystep < 0))
		ystep = -ystep;

	double nx = xint;
	double ny = yint;

	while (nx >= 0 && nx <= g->map_w * TILE && ny >= 0 && ny <= g->map_h * TILE)
	{
		int cx = (int)nx;
		if (ray->ray_left) cx -= 1;
		if (is_wall_pixel(g, cx, (int)ny))
		{
			*vx = nx; *vy = ny;
			return;
		}
		nx += xstep;
		ny += ystep;
	}
}