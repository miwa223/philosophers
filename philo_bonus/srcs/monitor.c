#include "philo_bonus.h"
#include "utils.h"

bool	is_died(t_thread *philo, int i)
{
	long	prev_eat_time;

	sem_wait(philo->monitor->sem_time);
	prev_eat_time = philo->prev_eat_time;
	sem_post(philo->monitor->sem_time);
	if (get_usec() - prev_eat_time > philo->data->die_usec)
	{
		sem_wait(philo->monitor->sem_end);
		philo->monitor->end = true;
		printf("%ld %d died\n", get_usec() / 1000, i + 1);
		return (true);
	}
	return (false);
}

bool	ate_enough(t_thread *philo)
{
	int	eat_count;

	sem_wait(philo->monitor->sem_count);
	eat_count = philo->eat_count;
	sem_post(philo->monitor->sem_count);
	return (eat_count >= philo->data->eat_times);
}

void	raise_end_flag(t_thread *philo)
{
	sem_wait(philo->monitor->sem_end);
	philo->monitor->end = true;
	sem_post(philo->monitor->sem_end);
}

void	*monitor(void *philo_thread)
{
	t_thread	*philo;
	int			i;

	philo = (t_thread *)philo_thread;
	while (1)
	{
		i = 0;
		if (is_died(philo, i))
			return (NULL);
		if (philo->data->eat_times != -1 && ate_enough(philo))
		{
			raise_end_flag(philo);
			return (NULL);
		}
		sleep_loop_usec(800, get_usec());
	}
	return (NULL);
}
