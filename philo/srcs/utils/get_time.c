#include "utils.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	sleep_loop(unsigned int	time_to_sleep, long past_time)
{
	while (get_time() - past_time < time_to_sleep)
		usleep(100);
}
