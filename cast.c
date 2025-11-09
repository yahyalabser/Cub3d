#include "cub3d.h"

static void set_ray_dirs(t_ray *ray)
{
	ray->ray_down  = (ray->ray_angle > 0 && ray->ray_angle < M_PI);
	ray->ray_up    = !ray->ray_down;
	ray->ray_right = (ray->ray_angle < 0.5*M_PI || ray->ray_angle > 1.5*M_PI);
	ray->ray_left  = !ray->ray_right;
}

static double dist2(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1, dy = y2 - y1;
	return sqrt(dx*dx + dy*dy);
}

t_ray *cast_single_ray(t_game *g, double ray_angle)
{
	t_ray *ray = malloc(sizeof(*ray));
	if (!ray) return NULL;

	ray->ray_angle = normalize_angle(ray_angle);
	ray->wallhitx = ray->wallhity = 0.0;
	ray->distance = (double)INT_MAX;
	ray->hit_vertical = 0;
	set_ray_dirs(ray);

	double hx, hy, vx, vy;
	find_horizontal_hit(g, ray, &hx, &hy);
	find_vertical_hit  (g, ray, &vx, &vy);

	double dh = (hx==INT_MAX || hy==INT_MAX) ? (double)INT_MAX : dist2(g->pl.x, g->pl.y, hx, hy);
	double dv = (vx==INT_MAX || vy==INT_MAX) ? (double)INT_MAX : dist2(g->pl.x, g->pl.y, vx, vy);

	if (dh <= dv)
	{
		ray->wallhitx = hx;
		ray->wallhity = hy;
		ray->distance = dh;
		ray->hit_vertical = 0;
	}
	else
	{
		ray->wallhitx = vx;
		ray->wallhity = vy;
		ray->distance = dv;
		ray->hit_vertical = 1;
	}
	return ray;
}

t_ray **cast_all_rays(t_game *g)
{
	t_ray **rays = malloc(sizeof(t_ray*) * NUM_RAYS);
	if (!rays) return NULL;
	double start = g->pl.angle - (FOV / 2.0);
	double step  = FOV / (double)NUM_RAYS;

	for (int i=0; i<NUM_RAYS; ++i)
		rays[i] = cast_single_ray(g, start + i*step);
	return rays;
}