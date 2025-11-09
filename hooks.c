#include "cub3d.h"

int on_close(t_game *g)
{
	(void)g;
	exit(0);
	return 0;
}

int on_key_press(int key, t_game *g)
{
	if (key == KEY_ESC) on_close(g);
	else if (key == KEY_LEFT)  g->pl.turn_dir   = -1;
	else if (key == KEY_RIGHT) g->pl.turn_dir   = +1;
	else if (key == KEY_W)     g->pl.walk_dir   = +1;
	else if (key == KEY_S)     g->pl.walk_dir   = -1;
	else if (key == KEY_A)     g->pl.strafe_dir = -1;
	else if (key == KEY_D)     g->pl.strafe_dir = +1;
	return 0;
}

int on_key_release(int key, t_game *g)
{
	if (key == KEY_LEFT || key == KEY_RIGHT) g->pl.turn_dir = 0;
	else if (key == KEY_W || key == KEY_S)   g->pl.walk_dir = 0;
	else if (key == KEY_A || key == KEY_D)   g->pl.strafe_dir = 0;
	return 0;
}

int on_loop(t_game *g)
{
	/* rotate */
	g->pl.angle += g->pl.turn_dir * g->pl.rot_speed;
	g->pl.angle = normalize_angle(g->pl.angle);

	/* movement */
	double fwd = g->pl.walk_dir * g->pl.move_speed;
	double str = g->pl.strafe_dir * g->pl.move_speed;

	double dx = cos(g->pl.angle) * fwd + cos(g->pl.angle + M_PI/2.0) * str;
	double dy = sin(g->pl.angle) * fwd + sin(g->pl.angle + M_PI/2.0) * str;

	/* Attempt X move */
	double nx = g->pl.x + dx;
	double ny = g->pl.y;
	if (!is_blocked(g, nx, ny)) g->pl.x = nx;

	/* Attempt Y move */
	nx = g->pl.x;
	ny = g->pl.y + dy;
	if (!is_blocked(g, nx, ny)) g->pl.y = ny;

	/* Render */
	render_frame(g);
	mlx_put_image_to_window(g->mlx, g->win, g->frame.img, 0, 0);
	return 0;
}