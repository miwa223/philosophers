#include "utils.h"

int	ft_atoi(char *str, int *overflow)
{
	int	i;
	int	sign;
	int	num;

	i = 0;
	sign = 1;
	num = 0;
	if (overflow != NULL)
		*overflow = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && ft_isdigit(str[i]) == 1)
	{
		num = num * 10 + (str[i] - '0');
		if (num < 0)
			*overflow = 1;
		i++;
	}
	return (num * sign);
}
