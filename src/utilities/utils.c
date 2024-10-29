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

void	*ft_memdup(void *src, size_t size)
{
	void	*new;

	new = malloc(size);
	if (!new)
		return (NULL);
	while (size--)
		((char *)new)[size] = ((char *)src)[size];
	return (new);
}
