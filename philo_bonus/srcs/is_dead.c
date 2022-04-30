#include "philo_bonus.h"
#include "utils.h"

bool	is_dead(t_thread *philo)
{
	if (philo->data->num == 1
		|| get_usec() - philo->prev_eat_time > philo->data->die_usec)
	{
		if (philo->data->num == 1)
			sleep_loop_usec(philo->data->die_usec, philo->prev_eat_time);
		sem_wait(philo->monitor->sem_end);
		printf("%ld %d died\n", get_usec() / 1000, philo->id + 1);
		return (true);
	}
	return (false);
}
