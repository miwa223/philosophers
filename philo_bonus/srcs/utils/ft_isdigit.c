#include "utils.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

bool	is_digit(char **argv, int i)
{
	size_t	j;

	j = 0;
	while (argv[i][j] && ft_isdigit(argv[i][j]) == 1)
		j++;
	if (ft_strlen(argv[i]) != j)
		return (false);
	return (true);
}
