#include "philo.h"

void	*monitor(void *philo_thread)
{
	t_thread	*philo;
	int			i;

	philo = (t_thread *)philo_thread;
	i = 0;
	while (!philo->monitor->end)
		usleep(100);
	while (i < philo->data->num)
	{
		pthread_mutex_unlock(&philo->fork[i]->mutex);
		i++;
	}
	return (NULL);
}
