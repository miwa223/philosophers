#include "utils.h"

long	get_usec(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return (tv.tv_sec * 1000 * 1000 + tv.tv_usec);
}

void	sleep_loop_usec(unsigned int need_to_sleep_usec, long past_time_usec)
{
	while (get_usec() - past_time_usec < need_to_sleep_usec)
		usleep(200);
}
