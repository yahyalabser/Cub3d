#include "cub3d.h"

void load_texture_or_die(t_img *img, void *mlx, const char *path)
{
	img->img = mlx_xpm_file_to_image(mlx, (char*)path, &img->w, &img->h);
	if (!img->img) { fprintf(stderr, "Failed to load texture: %s\n", path); exit(1); }
	img->data = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
	if (!img->data) { fprintf(stderr, "Failed to get texture data: %s\n", path); exit(1); }
}

void put_px(t_game *g, int x, int y, int color)
{
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
	int offset = y * g->frame.line_len + x * (g->frame.bpp / 8);
	*(int*)(g->frame.data + offset) = color;
}

void clear_frame(t_game *g)
{
	int *dst = (int*)g->frame.data;
	int pitch = g->frame.line_len / 4;
	for (int y=0; y<HEIGHT; ++y)
		for (int x=0; x<WIDTH; ++x)
			dst[y*pitch + x] = 0x000000;
}

int get_texel(t_img *img, int x, int y)
{
	if (!img || !img->data) return 0;
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x >= img->w) x = img->w - 1;
	if (y >= img->h) y = img->h - 1;
	int bpp = img->bpp / 8;
	int off = y * img->line_len + x * bpp;
	return *(int*)(img->data + off);
}

double clamp_min(double v, double minv)
{
	return (v < minv) ? minv : v;
}

double normalize_angle(double a)
{
	a = fmod(a, 2.0*M_PI);
	if (a < 0) a += 2.0*M_PI;
	return a;
}

/* Map sampling: pixel -> map cell; out-of-bounds => wall */
int is_wall_pixel(t_game *g, int x, int y)
{
	int mx = x / TILE;
	int my = y / TILE;
	if (my < 0 || my >= g->map_h) return 1;
	if (mx < 0 || mx >= g->map_w) return 1;
	char c = g->map[my][mx];
	/* treat spaces or null as walls, like parsing */
	if (c == '1' || c == ' ' || c == '\0')
		return 1;
	return 0;
}

/* Movement collision with buffer box */
int is_blocked(t_game *g, double x, double y)
{
	int mx1 = (int)((x - COLLISION_BUF) / TILE);
	int my1 = (int)((y - COLLISION_BUF) / TILE);
	int mx2 = (int)((x + COLLISION_BUF) / TILE);
	int my2 = (int)((y + COLLISION_BUF) / TILE);

	if (mx1 < 0 || my1 < 0 || mx2 >= g->map_w || my2 >= g->map_h) return 1;

	return (g->map[my1][mx1] == '1' || g->map[my1][mx2] == '1' ||
	        g->map[my2][mx1] == '1' || g->map[my2][mx2] == '1');
}

/* Find spawn and initial angle */
static void set_angle_from_char(t_game *g, char c)
{
	if (c == 'N') g->pl.angle = 3*M_PI/2.0;
	else if (c == 'E') g->pl.angle = 0.0;
	else if (c == 'W') g->pl.angle = M_PI;
	else if (c == 'S') g->pl.angle = M_PI/2.0;
}

void find_player_spawn(t_game *g)
{
	for (int r=0; r<g->map_h; ++r)
	{
		for (int c=0; c<g->map_w; ++c)
		{
			char ch = g->map[r][c];
			if (ch=='N'||ch=='E'||ch=='S'||ch=='W')
			{
				g->pl.x = c * TILE + TILE/2.0;
				g->pl.y = r * TILE + TILE/2.0;
				set_angle_from_char(g, ch);
				return;
			}
		}
	}
	/* fallback */
	g->pl.x = TILE/2.0;
	g->pl.y = TILE/2.0;
	g->pl.angle = 0.0;
}