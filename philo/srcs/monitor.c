#include "philo.h"

void	*monitor(void *philo_thread)
{
	t_thread	**philo;
	int			i;

	philo = (t_thread **)philo_thread;
	while (!philo[0]->monitor->end)
	{
		i = 0;
		while (philo[i])
		{
			if (!philo[i]->eat_done)
				break ;
			i++;
		}
		if (i == philo[0]->data->num)
			break ;
		usleep(100);
	}
	i = 0;
	while (i < philo[0]->data->num)
	{
		pthread_mutex_unlock(&philo[0]->fork[i]->mutex);
		i++;
	}
	return (NULL);
}
