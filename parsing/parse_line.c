#include "../cub3d.h"

static char *clean_path(char *path)
{
    int len;

	while (*path == ' ' || *path == '\t')
		path++;
    len = ft_strlen(path);
    while (len > 0 && (path[len - 1] == ' ' || path[len - 1] == '\t'))
    {
        path[len - 1] = '\0';
        len--;
    }
	return (path);
}

static int file_exists(char *path)
{
    int fd;

    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (0);
    close(fd);
    return (1);
}

static void parse_texture(int len, char **texture_ptr, char *line, int i)
{
    char    *path;

	if (*texture_ptr != NULL)
		exit_error("Error:\ninvalid map\n");
    path = clean_path(line + i + len);
    if (!file_exists(path))
	{
        exit_error("Error:\nTexture file not found\n");
	}
	*texture_ptr = ft_strdup(path);
	if (*texture_ptr == NULL)
		exit_error("Error:\nmemory allocation failed\n");
}

static void parse_config_color(int len, int *color_ptr, char *line, int i)
{
	if (*color_ptr != -1)
		exit_error("Error:\ninvalid color\n");
	*color_ptr = parse_color(clean_path(line + i + len));
	if (*color_ptr == -1)
		exit_error("Error:\ninvalid color\n");
}

int	parse_identifier(char *line, int i, t_config *config)
{
	if (ft_strncmp(line + i, "NO ", 3) == 0)
		parse_texture(3, &config->no_texture, line, i);
	else if (ft_strncmp(line + i, "SO ", 3) == 0)
		parse_texture(3, &config->so_texture, line, i);
	else if (ft_strncmp(line + i, "WE ", 3) == 0)
		parse_texture(3, &config->we_texture, line, i);
	else if (ft_strncmp(line + i, "EA ", 3) == 0)
		parse_texture(3, &config->ea_texture, line, i);
	else if (ft_strncmp(line + i, "F ", 2) == 0)
		parse_config_color(2, &config->floor_color, line, i);
	else if (ft_strncmp(line + i, "C ", 2) == 0)
		parse_config_color(2, &config->ceiling_color, line, i);
	else
		return (0);
	return (1);
}