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

int main(int argc, char **argv)
{
   t_config config;

   if (argc == 2)
   {
      init_config(&config);
      if (!parse_file(argv[1], &config))
         exit_error("Error:\ninvalid map.\n");
   }
   else
      exit_error("Error:\nno map specified.\n");
   
   free_all(&config);
   return (EXIT_SUCCESS);
}
