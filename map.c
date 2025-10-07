#include "cub3d.h"

int	is_map_line(char *line)
{
   int   i;

   if (!line)
      return 0;
   i = -1;
	while (line[++i])
		if (line[i] == '1' || line[i] == '0' ||
			line[i] == 'N' || line[i] == 'S' ||
			line[i] == 'E' || line[i] == 'W')
			return 1;
	return 0;
}

static int	is_valid_map_char(char c)
{
	return (c == '1' || c == '0' || c == 'N' || c == 'S' 
			|| c == 'W' || c == 'E' || c == ' ' 
			|| c == '\n' || c == '\r' || c == '\0');
}

static int is_a_map(char **map)
{
   int   i;
   int   j;

   i = -1;
   while (map[++i])
   {
      j = -1;
      while (map[i][++j])
      {
         if (!is_valid_map_char(map[i][j]))
            return (0);
      }
   }
   return (1);
}

int	validate_map_content(char **arr, int rows, int cols)
{
	int	i;
	int   j;
	int	players;
	
	players = 0;
	i = -1;
	while (++i < rows)
	{
      j = -1;
		while (++j < cols)
		{
			if (arr[i][j] == 'N' || arr[i][j] == 'S' ||
				arr[i][j] == 'E' || arr[i][j] == 'W')
				players++;
			if (arr[i][j] != '1' && arr[i][j] != ' ' && arr[i][j] != '\0')
			{
				if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1)
					return (0);
				if (arr[i - 1][j] == ' ' || arr[i + 1][j] == ' ' ||
					arr[i][j - 1] == ' ' || arr[i][j + 1] == ' ')
					return (0);
			}
		}
	}
	return (players == 1);
}

static void	calculate_dimensions(t_str *map, int *count, int *max)
{
	t_str	*tmp;
	int		len;

	tmp = map;
	*count = 0;
	*max = 0;
	while (tmp)
	{
		len = ft_strlen(tmp->content);
		if (len > 0 && tmp->content[len - 1] == '\n')
			len -=2;
		if (len > *max)
			*max = len;
		(*count)++;
		tmp = tmp->next;
	}
}

static char	**create_map_array(t_str *map, int count, int max)
{
	char	**arr;
	t_str	*tmp;
	int		i;
	int		len;

	arr = malloc((count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	tmp = map;
	i = -1;
	while (++i < count)
	{
		len = ft_strlen(tmp->content);
		if (len > 0 && tmp->content[len - 1] == '\n')
			len -= 2;
		arr[i] = malloc(max + 1);
		if (!arr[i])
			return (free_array(arr), NULL);
		ft_memset(arr[i], ' ', max);
		ft_memcpy(arr[i], tmp->content, len);
		arr[i][max] = '\0';
		tmp = tmp->next;
	}
	arr[count] = NULL;
	return (arr);
}

int	validate_map(t_config *config)
{
	int   count = 0;
   int   max = 0;
   char  **arr;
   int   result;

	calculate_dimensions(config->map, &count, &max);
	if (count < 3 || max < 3)
		return ( 0);
	arr = create_map_array(config->map, count, max);
	if (!arr)
      	return (0);
	if (!is_a_map(arr))
	{
    	free_array(arr);
    	return 0;
   	}
   	result = validate_map_content(arr, count, max);
	if (result == 1)
	{
		config->map_array = arr;
		config->map_height = count;
		config->map_width = max;
		free_map(config->map);
		config->map = NULL;
	}
	else
		free_array(arr);
	return (result);
}
