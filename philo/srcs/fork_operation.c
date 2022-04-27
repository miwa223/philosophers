#include "philo.h"
#include "utils.h"

bool	check_fork_is_remaining(t_thread *philo, int num)
{
	bool	prev_status;

	prev_status = false;
	pthread_mutex_lock(&philo->fork[num]->mutex);
	prev_status = philo->fork[num]->taken;
	philo->fork[num]->taken = true;
	pthread_mutex_unlock(&philo->fork[num]->mutex);
	return (prev_status);
}

void	take_a_fork(bool (*func)(t_thread *, int), t_thread *philo, int num)
{
	while (!is_end(philo))
	{
		if (!func(philo, num))
		{
			printf("%ld %d has taken a fork\n", get_time(), philo->id + 1);
			break ;
		}
		sleep_loop(1, get_time());
	}
}

void	put_back_forks(t_thread *philo)
{
	pthread_mutex_lock(&philo->fork[philo->id]->mutex);
	philo->fork[philo->id]->taken = false;
	pthread_mutex_unlock(&philo->fork[philo->id]->mutex);
	pthread_mutex_lock(&philo->fork[(philo->id + 1) % philo->data->num]->mutex);
	philo->fork[(philo->id + 1) % philo->data->num]->taken = false;
	pthread_mutex_unlock(
		&philo->fork[(philo->id + 1) % philo->data->num]->mutex);
}
