#include "cub3d.h"

void	free_array(char **arr)
{
	if (!arr)
      return;
	for (int i = 0; arr[i]; i++)
		free(arr[i]);
	free(arr);
}

void	free_map(t_str *map)
{
	t_str *tmp;

	while (map)
	{
		tmp = map->next;
		free(map->content);
		free(map);
		map = tmp;
	}
}

void	free_config(t_config *config)
{
	free(config->no_texture);
	free(config->so_texture);
	free(config->we_texture);
	free(config->ea_texture);
}

void	free_all(t_config *config)
{
	free_config(config);
	free_map(config->map);
}