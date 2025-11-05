#include "../cub3d.h"

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

static int	skip_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

static int	is_empty_line(char *line, int i)
{
	return (line[i] == '\n' || !line[i] || line[i] == '\r');
}

static void	handle_empty_line(char *line, t_config *config, int *map_started)
{
	if (*map_started == 1)
	{
		free(line);
		free_all(config);
		exit_error("Error:\ninvalid map\n");
	}
}

static void trim_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n')
	{
        line[len - 2] = '\0';
	}
}

static void	parse_line(char *line, t_config *config, int *map_started)
{
	int i;

	i = skip_whitespace(line);
    if (is_empty_line(line, i)) 
    {
        handle_empty_line(line, config, map_started);
        return ;
    }
	trim_newline(line);
	if (parse_identifier(line, i, config))
		return ;
	if (is_map_line(line))
	{
		*map_started = 1;
		str_add_back(&(config->map), line);
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
	if (!config->map || !validate_map(config))
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
	if (i < 5 || ft_strcmp(file + i - 4, ".cub") != 0)
		return 0;
	int fd = open(file, O_RDONLY);
	if (fd < 0)
		return 0;
	return parse_content(fd, config);
}
