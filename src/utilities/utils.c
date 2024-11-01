#include "cube.h"

size_t	ft_strlen(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	return (i);
}


char	*ft_strdup(char *str)
{
	char	*new;
	int		i;

	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

void	*ft_bzero(void *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = size / sizeof(void *);
	i = -1;
	while (++i < len)
		*((void **)src + i) = (void *)0;
	len = size % sizeof(void *);
	i = -1;
	while (++i < len)
		*((char *)src + i) = 0;
	return (src);
}
