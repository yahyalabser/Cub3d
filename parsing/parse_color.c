#include "../cub3d.h"

typedef struct s_color_parser
{
	int	r;
	int	g;
	int	b;
	int	i;
	int	count;
	int	comma_count;
}	t_color_parser;

static void	init_parser(t_color_parser *parser)
{
	parser->r = -1;
	parser->g = -1;
	parser->b = -1;
	parser->i = 0;
	parser->count = 0;
	parser->comma_count = 0;
}

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

static int	parse_number(char *line, int *i)
{
	int	val;
	int	has_digit;

	val = 0;
	has_digit = 0;
	if (line[*i] < '0' || line[*i] > '9')
		return (-1);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		has_digit = 1;
		val = val * 10 + (line[*i] - '0');
		(*i)++;
	}
	if (!has_digit || val > 255)
		return (-1);
	return (val);
}

static void	assign_color_value(t_color_parser *parser, int val)
{
	if (parser->count == 0)
		parser->r = val;
	else if (parser->count == 1)
		parser->g = val;
	else
		parser->b = val;
}

static int	validate_format(char *line, t_color_parser *parser)
{
	if (line[parser->i] != '\0' || parser->comma_count != 2)
		return (0);
	if (parser->r < 0 || parser->r > 255)
		return (0);
	if (parser->g < 0 || parser->g > 255)
		return (0);
	if (parser->b < 0 || parser->b > 255)
		return (0);
	return (1);
}

int	parse_color(char *line)
{
	t_color_parser parser;
	int	val;

	init_parser(&parser);
	while (parser.count < 3)
	{
		if (parser.comma_count > 2)
			return (-1);
		skip_spaces(line, &parser.i);
		val = parse_number(line, &parser.i);
        if (val < 0)
            return (-1);
		assign_color_value(&parser, val);
		parser.count++;
		skip_spaces(line, &parser.i);
		if (parser.count < 3)
		{
			if (line[parser.i] != ',')
				return (-1);
			parser.comma_count++;
			parser.i++;
		}
	}
	if (!validate_format(line, &parser)) 
		return (-1);
	return (parser.r << 16 | parser.g << 8 | parser.b);
}
