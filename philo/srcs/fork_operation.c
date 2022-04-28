#include "philo.h"
#include "utils.h"

long	take_a_fork(t_thread *philo, int num)
{
	long	time;

	pthread_mutex_lock(&philo->fork[num]->mutex);
	// if (!philo->fork[num]->taken)
	// {
	// philo->fork[num]->taken = true;
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
	// }
	// return (true);
}

void	put_back_forks(t_thread *philo)
{
	// philo->fork[philo->id]->taken = false;
	pthread_mutex_unlock(&philo->fork[philo->id]->mutex);
	// philo->fork[(philo->id + 1) % philo->data->num]->taken = false;
	pthread_mutex_unlock(
		&philo->fork[philo->left_fork_id]->mutex);
}
