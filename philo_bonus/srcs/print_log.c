#include "philo_bonus.h"
#include "utils.h"

long	print_log(t_thread *philo, char *msg)
{
	long	now;

	sem_wait(philo->monitor->sem_end);
	if (philo->monitor->end)
	{
		sem_post(philo->monitor->sem_end);
		return (0);
	}
	now = get_usec();
	printf("%ld %d %s\n", now / 1000, philo->id + 1, msg);
	sem_post(philo->monitor->sem_end);
	return (now);
}
