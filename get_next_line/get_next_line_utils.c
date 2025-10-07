/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:45:58 by ylabser           #+#    #+#             */
/*   Updated: 2024/12/08 11:54:08 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	found_newline(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char *s1, char *s2, int size)
{
	int		i;
	int		j;
	int		len;
	char	*buffer;

	if (!s2 || size < 0)
		return (NULL);
	if (!s1)
		s1 = ft_init(NULL);
	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + size;
	buffer = malloc(len + 1);
	if (!buffer)
	{
		free(s1);
		return (NULL);
	}
	i = -1;
	while (s1[++i] != '\0')
		buffer[i] = s1[i];
	j = 0;
	while (s2[j] != '\0' && j < size)
	{
		buffer[i + j] = s2[j];
		j++;
	}
	buffer[i + j] = '\0';
	free(s1);
	return (buffer);
}

char	*ft_init(char *str)
{
	char	*result;

	(void)str;
	result = malloc(1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	return (result);
}
