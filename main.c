#include "cub3d.h"

int exit_error(char *mssg)
{
   if (mssg)
      write(1, mssg, ft_strlen(mssg));
   exit (EXIT_FAILURE);
}

static void init_config(t_config *config)
{
   config->no_texture = NULL;
   config->ea_texture = NULL;
   config->we_texture = NULL;
   config->so_texture = NULL;
   config->floor_color = -1;
   config->ceiling_color = -1;
   config->map = NULL;
   config->map_array = NULL;
   config->map_height = 0;
   config->map_width = 0;
}


static void set_initial_player_speeds(t_game *g)
{
	g->pl.move_speed = 3.0;
	g->pl.rot_speed  = (3.0 * M_PI) / 180.0; /* 3 deg/frame */
	g->pl.walk_dir   = 0;
	g->pl.strafe_dir = 0;
	g->pl.turn_dir   = 0;
}

int game_init_from_config(t_game *g, t_config *cfg)
{
	memset(g, 0, sizeof(*g));

	/* Copy map & colors */
	g->map      = cfg->map_array;
	g->map_w    = cfg->map_width;
	g->map_h    = cfg->map_height;
	g->ceil_color  = cfg->ceiling_color;
	g->floor_color = cfg->floor_color;

	/* Init MLX */
	g->mlx = mlx_init();
	if (!g->mlx) return (fprintf(stderr, "mlx_init failed\n"), 0);
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!g->win) return (fprintf(stderr, "mlx_new_window failed\n"), 0);
	g->frame.img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->frame.img) return (fprintf(stderr, "mlx_new_image failed\n"), 0);
	g->frame.data = mlx_get_data_addr(g->frame.img, &g->frame.bpp, &g->frame.line_len, &g->frame.endian);
	if (!g->frame.data) return (fprintf(stderr, "mlx_get_data_addr failed\n"), 0);

	/* Load NESW */
	load_texture_or_die(&g->tex_n, g->mlx, cfg->no_texture);
	load_texture_or_die(&g->tex_s, g->mlx, cfg->so_texture);
	load_texture_or_die(&g->tex_e, g->mlx, cfg->ea_texture);
	load_texture_or_die(&g->tex_w, g->mlx, cfg->we_texture);

	/* Player spawn & speeds */
	find_player_spawn(g);
	set_initial_player_speeds(g);

	return 1;
}

void game_shutdown(t_game *g)
{
	if (g->frame.img) mlx_destroy_image(g->mlx, g->frame.img);
	if (g->win) mlx_destroy_window(g->mlx, g->win);
	/* Do not free map/textures here if parsing module frees them later.
	   If you own them, add image destroys for tex_n/s/e/w: */
	/* mlx_destroy_image(g->mlx, g->tex_n.img); ... */
}

int main(int argc, char **argv)
{
	t_config cfg;
	t_game   g;

	if (argc != 2)
		return (write(1, "Error:\nno map specified.\n", 25), EXIT_FAILURE);

	/* parse */
	memset(&cfg, 0, sizeof(cfg));
	if (!parse_file(argv[1], &cfg))
		return (write(1, "Error:\ninvalid map.\n", 20), EXIT_FAILURE);

	/* init engine from config */
	if (!game_init_from_config(&g, &cfg))
	{
		free_all(&cfg);
		return (EXIT_FAILURE);
	}

	/* First frame */
	render_frame(&g);
	mlx_put_image_to_window(g.mlx, g.win, g.frame.img, 0, 0);

	/* hooks */
	mlx_hook(g.win, 17, 0, on_close, &g);
	mlx_hook(g.win, 2, 1L<<0, on_key_press, &g);
	mlx_hook(g.win, 3, 1L<<1, on_key_release, &g);
	mlx_loop_hook(g.mlx, on_loop, &g);
	mlx_loop(g.mlx);

	/* cleanup config structure once the loop ends (or in on_close) */
	free_all(&cfg);
	return 0;
}














// int main(int argc, char **argv)
// {
//    t_config config;

//    if (argc == 2)
//    {
//       init_config(&config);
//       if (!parse_file(argv[1], &config))
//          exit_error("Error:\ninvalid map.\n");
//    }
//    else
//       exit_error("Error:\nno map specified.\n");
   
//    free_all(&config); // a remplacer dans close window
//    return (EXIT_SUCCESS);
// }

// int main(int argc , char **argv)
// {
//    t_config config;
//    if (argc !=2)
//       exit_error("Error:\nno map specified.\n");
//    init_config(&config);
//    if (!parse_file(argv[1], &config))
//       exit_error("Error:\ninvalid map.\n");
   
//    //int_app(&game)
//    // find player postion 
//    // create a map
//    return(EXIT_SUCCESS);
   
// }

// int main(int argc, char **argv)
// {
//    t_config config;

//    if (argc == 2)
//    {
//       init_config(&config);
//       if (!parse_file(argv[1], &config))
//          exit_error("Error:\ninvalid map.\n");
//       printf("%s\n", config.map_array[1]);
//    }
//    else
//       exit_error("Error:\nno map specified.\n");
   
//    free_all(&config);
//    return (EXIT_SUCCESS);
// }