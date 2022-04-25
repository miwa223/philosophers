#include "philo.h"

void	*free_fork(t_fork **fork)
{
	int	i;

	i = 0;
	while (fork[i])
	{
		pthread_mutex_unlock(&fork[i]->mutex);
		pthread_mutex_destroy(&fork[i]->mutex);
		free(fork[i]);
		i++;
	}
	free(fork);
	return (NULL);
}

void	*free_contents(t_fork **fork, t_monitor *monitor, t_thread **philo)
{
	int	i;

	i = 0;
	if (fork)
		free_fork(fork);
	if (monitor)
		free(monitor);
	if (philo)
	{
		while (philo[i])
		{
			free(philo[i]);
			i++;
		}
		free(philo);
	}
	return (NULL);
}
