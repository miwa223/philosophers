#include "philo.h"
#include "utils.h"

long	print_msg(t_thread *philo, char *str)
{
	long	now;

	pthread_mutex_lock(&philo->monitor->mutex);
	if (philo->monitor->end)
	{
		pthread_mutex_unlock(&philo->monitor->mutex);
		return (0);
	}
	now = get_usec();
	printf("%ld %d %s\n", now / 1000, philo->id + 1, str);
	pthread_mutex_unlock(&philo->monitor->mutex);
	return (now);
}
