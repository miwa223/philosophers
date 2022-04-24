#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>

int		ft_atoi(char *str, int *overflow);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
long	get_time(void);
int		exit_program(int type);

#endif
