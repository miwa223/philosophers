#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <limits.h>

# define ERROR -1

int		ft_atoi(char *str, int *overflow);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
void	exit_program(int status);

#endif
