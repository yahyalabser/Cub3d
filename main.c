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
   config->floor_color = 0;
   config->ceiling_color = 0;
   config->map = NULL;
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
   return (EXIT_SUCCESS);
}
