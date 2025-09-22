#include "cub3d.h"

int	ft_strlen(char *s)
{
	int	i;

   if (!s)
      return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_strcmp(char *s1, char *s2)
{
    unsigned char *p1;
    unsigned char *p2;

    p1 = (unsigned char *)s1;
    p2 = (unsigned char *)s2;
    while (*p1 && *p1 == *p2)
   {
      p1++;
      p2++;
   }
    return (*p1 - *p2);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
	{
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (0);
}

char	*ft_strdup(char *src)
{
	char	*p;
	int		i;

	p = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	*ft_memcpy(char *dst, char *src, size_t n)
{
	unsigned char		*str1;
	const unsigned char	*str2;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (n == 0)
		return (dst);
	str1 = (unsigned char *)dst;
	str2 = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		str1[i] = str2[i];
		i++;
	}
	return (dst);
}

void	*ft_memset(char *b, int c, size_t len)
{
	char			*str;
	unsigned char	car;

	str = (char *)b;
	car = (unsigned char)c;
	while (len)
	{
		*str = car ;
		str++;
		len--;
	}
	return (b);
}
