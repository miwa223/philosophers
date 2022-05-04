#include "philo_bonus.h"
#include "utils.h"

void	*monitor(void *philo_thread)
{
	t_thread	*philo;
	long		eat_time;

	philo = (t_thread *)philo_thread;
	while (1)
	{
		sem_wait(philo->monitor->sem_time);
		eat_time = philo->prev_eat_time;
		sem_post(philo->monitor->sem_time);
		if (get_usec() - eat_time > philo->data->die_usec)
		{
			sem_wait(philo->monitor->sem_end);
			printf("%ld %d died\n", get_usec() / 1000, philo->id + 1);
			return (NULL);
		}
		sleep_loop_usec(800, get_usec());
	}
	return (NULL);
}
