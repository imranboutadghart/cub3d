#include "cube.h"

int	error(char *msg)
{
	int bruv = write(2, msg, ft_strlen(msg));
	(void)bruv;
	return (1);
}
