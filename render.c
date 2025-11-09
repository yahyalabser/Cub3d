#include "cub3d.h"

static void draw_ceiling_column(t_game *g, int x, int top)
{
	for (int y=0; y<top; ++y) put_px(g, x, y, g->ceil_color);
}

static void draw_floor_column(t_game *g, int x, int bottom)
{
	for (int y=bottom+1; y<HEIGHT; ++y) put_px(g, x, y, g->floor_color);
}

static t_img *select_texture(t_game *g, t_ray *ray)
{
	(void)g;
	if (ray->hit_vertical)
		return ray->ray_right ? &g->tex_e : &g->tex_w;
	else
		return ray->ray_up ? &g->tex_n : &g->tex_s;
}

static double hit_offset_in_tile(const t_ray *ray)
{
	double off = ray->hit_vertical ? fmod(ray->wallhity, TILE)
	                               : fmod(ray->wallhitx, TILE);
	if (off < 0) off += TILE;
	return off;
}

static void draw_textured_slice(t_game *g, int screen_x,
                                int wall_top, int wall_bottom,
                                double wall_h, t_ray *ray)
{
	t_img *tex = select_texture(g, ray);

	/* texture X */
	double off = hit_offset_in_tile(ray);
	int tex_x = (int)((off / TILE) * tex->w);
	if (tex_x < 0) tex_x = 0;
	if (tex_x >= tex->w) tex_x = tex->w - 1;

	/* draw column */
	int top = wall_top < 0 ? 0 : wall_top;
	int bot = wall_bottom >= HEIGHT ? HEIGHT - 1 : wall_bottom;

	for (int y = top; y <= bot; ++y)
	{
		double sample = (double)(y - wall_top); /* from top of slice */
		int tex_y = (int)((sample / wall_h) * tex->h);
		if (tex_y < 0) tex_y = 0;
		if (tex_y >= tex->h) tex_y = tex->h - 1;

		int color = get_texel(tex, tex_x, tex_y);
		put_px(g, screen_x, y, color);
	}
}

void render_frame(t_game *g)
{
	clear_frame(g);

	/* projection plane distance */
	double dist_proj = (WIDTH / 2.0) / tan(FOV / 2.0);

	/* cast */
	t_ray **rays = cast_all_rays(g);
	if (!rays) return;

	for (int i=0; i<NUM_RAYS; ++i)
	{
		t_ray *ray = rays[i];
		int screen_x = i * WALL_STRIP;

		if (!ray || ray->distance <= 0 || ray->distance == (double)INT_MAX)
		{
			/* draw simple ceiling/floor for invalid ray column */
			draw_ceiling_column(g, screen_x, HEIGHT/2);
			draw_floor_column(g, screen_x, HEIGHT/2);
			if (ray) free(ray);
			continue;
		}

		/* fisheye correction */
		double corr = ray->distance * cos(ray->ray_angle - g->pl.angle);
		corr = clamp_min(corr, 0.0005);

		/* projection */
		double wall_h = (TILE / corr) * dist_proj;
		int wall_top = (int)((HEIGHT / 2.0) - (wall_h / 2.0));
		int wall_bottom = (int)((HEIGHT / 2.0) + (wall_h / 2.0));

		/* draw ceiling, slice, floor */
		int top_clamped = wall_top < 0 ? 0 : wall_top;
		draw_ceiling_column(g, screen_x, top_clamped);
		draw_textured_slice(g, screen_x, wall_top, wall_bottom, wall_h, ray);
		draw_floor_column(g, screen_x, wall_bottom);

		free(ray);
	}
	free(rays);
}