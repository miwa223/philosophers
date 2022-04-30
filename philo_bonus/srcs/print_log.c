#include "philo_bonus.h"
#include "utils.h"

long	print_log(t_thread *philo, char *msg)
{
	long	now;

	sem_wait(philo->monitor->sem_end);
	now = get_usec();
	if (!(philo->data->eat_times != -1
			&& philo->eat_count > philo->data->eat_times))
		printf("%ld %d %s\n", now / 1000, philo->id + 1, msg);
	sem_post(philo->monitor->sem_end);
	return (now);
}
