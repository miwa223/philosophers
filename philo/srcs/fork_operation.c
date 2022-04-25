#include "philo.h"

void	take_right_fork(t_thread *philo)
{
	while (!philo->monitor->end)
	{
		if (!philo->fork[philo->id]->taken
			&& !philo->fork[(philo->id + 1) % philo->data->num]->taken)
		{
			pthread_mutex_lock(&philo->fork[philo->id]->mutex);
			philo->fork[philo->id]->taken = true;
			break ;
		}
		usleep(50);
	}
	pthread_mutex_unlock(&philo->fork[philo->id]->mutex);
}

void	take_left_fork(t_thread *philo)
{
	while (!philo->monitor->end)
	{
		if (!philo->fork[(philo->id + 1) % philo->data->num]->taken)
		{
			pthread_mutex_lock(
				&philo->fork[(philo->id + 1) % philo->data->num]->mutex);
			philo->fork[(philo->id + 1) % philo->data->num]->taken = true;
			break ;
		}
		usleep(50);
	}
	pthread_mutex_unlock(
		&philo->fork[(philo->id + 1) % philo->data->num]->mutex);
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
