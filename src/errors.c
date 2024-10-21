#include "cube.h"

static int	ft_strlen(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
		i++;
	return (i);
}

int	error(char *msg)
{
	int bruv = write(2, msg, ft_strlen(msg));
	(void)bruv;
	return (1);
}
