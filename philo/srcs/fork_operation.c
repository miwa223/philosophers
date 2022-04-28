#include "philo.h"
#include "utils.h"

long	take_a_fork(t_thread *philo, int num)
{
	long	time;

	pthread_mutex_lock(&philo->fork[num]->mutex);
	time = print_msg(philo, "has taken a fork");
	if (time == 0)
	{
		if (num != philo->id)
			put_back_forks(philo);
		else
			pthread_mutex_unlock(&philo->fork[num]->mutex);
		return (0);
	}
	if (philo->data->num == 1)
	{
		pthread_mutex_unlock(&philo->fork[num]->mutex);
		return (0);
	}
	return (time);
}

void	put_back_forks(t_thread *philo)
{
	pthread_mutex_unlock(&philo->fork[philo->id]->mutex);
	pthread_mutex_unlock(
		&philo->fork[philo->left_fork_id]->mutex);
}
