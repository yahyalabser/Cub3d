/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabser <ylabser@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:46:55 by ylabser           #+#    #+#             */
/*   Updated: 2024/12/08 14:51:15 by ylabser          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include "../cub3d.h"

char		*get_next_line(int fd);
char		*ft_strjoin(char *s1, char *s2, int size);
// size_t		ft_strlen(char *str);
// char		*ft_strdup(char *s);
int			found_newline(char	*str);
char		*ft_init(char *str);

#endif