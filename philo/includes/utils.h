#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>

int		ft_atoi(char *str, int *overflow);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
bool	is_digit(char **argv, int i);
long	get_time(void);
void	sleep_loop(unsigned int	time_to_sleep, long past_time);

#endif
