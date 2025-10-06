#include "cub3d.h"

int	is_map_line(const char *line)
{
	for (int i = 0; line[i]; i++)
		if (line[i] == '1' || line[i] == '0' ||
			line[i] == 'N' || line[i] == 'S' ||
			line[i] == 'E' || line[i] == 'W')
			return 1;
	return 0;
}

static int is_a_map(char **map)
{
   int   i;
   int   j;

   i = 0;
   while (map[i])
   {
      j = 0;
      while (map[i][j])
      {
         if (map[i][j] == ' ' || map[i][j] == '\n' || map[i][j] == '\r')
         {
            j++;
            continue;
         }
         if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != 'S' && map[i][j] != 'N' && map[i][j] != 'W' && map[i][j] != 'E')
            return (0);
         j++;
      }
      i++;
   }
   return (1);
}

int	validate_map(t_str *map)
{
	int count = 0, max = 0, i = 0, j, len;
	t_str *tmp = map;
	// Compte le nombre de lignes et la largeur max
	while (tmp)
	{
		len = ft_strlen(tmp->content);
      if (len > 0 && tmp->content[len - 1] == '\n') len -= 2;
		if (len > max) max = len;
		count++;
		tmp = tmp->next;
	}
	if (count < 3 || max < 3)
		return ( 0);
	// Création d'un tableau 2D rempli d'espaces
	char **arr = malloc((count+1) * sizeof(char *));
	if (!arr) return (0);
	tmp = map;
	for (i = 0; i < count; i++)
	{
      len = ft_strlen(tmp->content);
      if (len > 0 && tmp->content[len - 1] == '\n') len -=2;
		arr[i] = malloc(max+1);
		if (!arr[i]) { free_array(arr);return 0; }
		// int len = ft_strlen(tmp->content);
		ft_memset(arr[i], ' ', max);
		ft_memcpy(arr[i], tmp->content, len);
		arr[i][max] = 0;
		tmp = tmp->next;
	}
	arr[count] = 0;

   if (!is_a_map(arr)) {free_array(arr); return 0; }
	// Vérifie bords et voisinages
	int players = 0;
	for (i = 0; i < count; i++)
   {
      for (j = 0; j < max; j++)
      {
         char c = arr[i][j];
         if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            players++;
         if (c != '1' && c != ' ' && c != '\r' && c != '\t')
         {
            if (i == 0 || i == count-1 || j == 0 || j == max-1 ||
               arr[i-1][j] == ' ' || arr[i+1][j] == ' ' ||
               arr[i][j-1] == ' ' || arr[i][j+1] == ' ')
               {free_array(arr); return 0; }
         }
      }
   }
	free_array(arr);
	return (players == 1);
}
