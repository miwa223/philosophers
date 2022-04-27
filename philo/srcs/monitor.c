#include "philo.h"
#include "utils.h"

bool	is_end(t_thread *philo)
{
	bool	end_flag;

	pthread_mutex_lock(&philo->monitor->mutex);
	end_flag = philo->monitor->end;
	pthread_mutex_unlock(&philo->monitor->mutex);
	return (end_flag);
}

bool	someone_died(t_thread *philo, int i)
{
	long	prev_eat_time;

	pthread_mutex_lock(&philo->mutex_time);
	prev_eat_time = philo->prev_eat_time;
	pthread_mutex_unlock(&philo->mutex_time);
	if (get_time() - prev_eat_time > philo->data->die_t)
	{
		raise_end_flag(philo);
		usleep(1000);
		printf("%ld %d died\n", get_time(), i + 1);
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
	return (eat_count == philo->data->eat_times);
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
	while (!is_end(philo[0]))
	{
		i = 0;
		count = 0;
		while (philo[i])
		{
			if (someone_died(philo[i], i))
				return (NULL);
			if (ate_enough(philo[i]))
				count++;
			i++;
		}
		if (count == philo[0]->data->num)
		{
			raise_end_flag(philo[0]);
			break ;
		}
		usleep(100);
	}
	return (NULL);
}
