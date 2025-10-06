#include "cub3d.h"

static void	str_add_back(t_str **str, char *line)
{
	t_str *new = malloc(sizeof(t_str));
	if (!new)
		exit_error("Error:\nmalloc failed\n");
	new->content = ft_strdup(line);
	if (!new->content)
		exit_error("Error:\nstrdup failed\n");
	new->next = NULL;
	if (!*str)
		*str = new;
	else
	{
		t_str *tmp = *str;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static int	parse_color(const char *line)
{
	int r = -1, g = -1, b = -1, i = 0, count = 0, comma_count = 0 ;
	while (count < 3)
	{
		int val = 0;
		int non_empty = 0;
		if (comma_count > 2) return -1;
		while (line[i] == ' ' || line[i] == '\t') i++;
		if (line[i] < '0' || line[i] > '9') return -1;
		while (line[i] >= '0' && line[i] <= '9')
		{
			non_empty = 1;
			val = val * 10 + (line[i++] - '0');
		}
		if (non_empty == 0 || val > 255) return -1;
		if (count == 0) r = val;
		else if (count == 1) g = val;
		else b = val;
		count++;
		while (line[i] == ' ' || line[i] == '\t') i++;
		if (count < 3)
		{
			if (line[i] != ',') return -1;
			comma_count++;
			i++;
		}
	}
	if (line[i] != '\0' || comma_count != 2) 
		return -1;
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return -1;
	return (r << 16 | g << 8 | b);
}

static char *clean_path(char *path)
{
	while (*path == ' ' || *path == '\t')
		path++;
	return (path);
}

void parse_texture(int len, char **texture_ptr, char *line, int i)
{
	if (*texture_ptr != NULL)
		exit_error("Error:\ninvalid map\n");
	*texture_ptr = ft_strdup(clean_path(line + i + len));
	if (*texture_ptr == NULL)
		exit_error("Error:\nmemory allocation failed\n");
}

void parse_config_color(int len, int *color_ptr, char *line, int i)
{
	if (*color_ptr != -1)
		exit_error("Error:\ninvalid color\n");
	*color_ptr = parse_color(clean_path(line + i + len));
	if (*color_ptr == -1)
		exit_error("Error:\ninvalid color\n");
}

void	parse_line(char *line, t_config *config, int *map_started)
{
	int i = 0;
	char *trimmed_line = line;

    while (trimmed_line[i] == ' ' || trimmed_line[i] == '\t') i++;
    if (trimmed_line[i] == '\n' || !trimmed_line[i] || trimmed_line[i] == '\r') 
      {
         if (*map_started == 1)
         {
            free(line);
            free_all(config);
            exit_error("Error:\nempty line in map\n");
         }
         return ;
    }

	int len = ft_strlen(trimmed_line);
    if (len > 0 && trimmed_line[len-1] == '\n')
	{
        trimmed_line[len-2] = '\0';
	}
	if (ft_strncmp(trimmed_line + i, "NO ", 3) == 0)
		parse_texture(3, &config->no_texture, trimmed_line, i);
	else if (ft_strncmp(trimmed_line + i, "SO ", 3) == 0)
		parse_texture(3, &config->so_texture, trimmed_line, i);
	else if (ft_strncmp(trimmed_line + i, "WE ", 3) == 0)
		parse_texture(3, &config->we_texture, trimmed_line, i);
	else if (ft_strncmp(trimmed_line + i, "EA ", 3) == 0)
		parse_texture(3, &config->ea_texture, trimmed_line, i);
	else if (ft_strncmp(trimmed_line + i, "F ", 2) == 0)
		parse_config_color(2, &config->floor_color, trimmed_line, i);
	else if (ft_strncmp(trimmed_line + i, "C ", 2) == 0)
		parse_config_color(2, &config->ceiling_color, trimmed_line, i);
	else if (is_map_line(trimmed_line))
	{
		*map_started = 1;
		str_add_back(&(config->map), trimmed_line);
	}
	else
		exit_error("Error:\ninvalid line\n");
}

static void	check_config(t_config *config)
{
	if (!config->no_texture || !config->so_texture ||
		!config->we_texture || !config->ea_texture)
	{
		free_all(config);
		exit_error("Error:\nMissing texture\n");
	}
	if (config->floor_color == -1 || config->ceiling_color == -1)
	{
		free_all(config);
		exit_error("Error:\nMissing color\n");
	}
	if (!config->map || !validate_map(config->map))
	{
		free_all(config);
		exit_error("Error:\nInvalid map\n");
	}
}

static int	parse_content(int fd, t_config *config)
{
	char *line;
	int map_started = 0;
	while ((line = get_next_line(fd)))
	{
		parse_line(line, config, &map_started);
		free(line);
	}
	check_config(config);
	close(fd);
	return 1;
}

int	parse_file(char *file, t_config *config)
{
	int i = ft_strlen(file);
	if (i <= 5 || ft_strcmp(file + i - 4, ".cub") != 0)
		return 0;
	int fd = open(file, O_RDONLY);
	if (fd < 0)
		return 0;
	return parse_content(fd, config);
}
