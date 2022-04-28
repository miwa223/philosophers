#include "philo.h"
#include "utils.h"

bool	someone_died(t_thread *philo, int i)
{
	long	prev_eat_time;

	pthread_mutex_lock(&philo->mutex_time);
	prev_eat_time = philo->prev_eat_time;
	pthread_mutex_unlock(&philo->mutex_time);
	if (get_usec() - prev_eat_time > philo->data->die_usec)
	{
		pthread_mutex_lock(&philo->monitor->mutex);
		philo->monitor->end = true;
		printf("%ld %d died\n", get_usec() / 1000, i + 1);
		pthread_mutex_unlock(&philo->monitor->mutex);
		return (true);
	}
	return (false);
}

bool	ate_enough(t_thread *philo)
{
	int	eat_count;

	pthread_mutex_lock(&philo->mutex_count);
	eat_count = philo->eat_count;
	pthread_mutex_unlock(&philo->mutex_count);
	return (eat_count >= philo->data->eat_times);
}

void	raise_end_flag(t_thread *philo)
{
	pthread_mutex_lock(&philo->monitor->mutex);
	philo->monitor->end = true;
	pthread_mutex_unlock(&philo->monitor->mutex);
}

void	*monitor(void *philo_thread)
{
	t_thread	**philo;
	int			i;
	int			count;

	philo = (t_thread **)philo_thread;
	while (1)
	{
		i = 0;
		count = 0;
		while (philo[i])
		{
			if (someone_died(philo[i], i))
				return (NULL);
			if (philo[i]->data->eat_times != -1 && ate_enough(philo[i]))
				count++;
			i++;
		}
		if (count == philo[0]->data->num)
		{
			raise_end_flag(philo[0]);
			break ;
		}
		sleep_loop_usec(1000, get_usec());
	}
	return (NULL);
}
