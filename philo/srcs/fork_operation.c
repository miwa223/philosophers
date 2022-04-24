#include "philo.h"

void	take_right_fork(t_thread *philo)
{
	while (1)
	{
		if (!philo->fork[philo->id]->taken
			&& !philo->fork[(philo->id + 1) % philo->data->num]->taken)
		{
			pthread_mutex_lock(&philo->fork[philo->id]->mutex);
			philo->fork[philo->id]->taken = true;
			break ;
		}
	}
	pthread_mutex_unlock(&philo->fork[philo->id]->mutex);
}

void	take_left_fork(t_thread *philo)
{
	while (1)
	{
		if (!philo->fork[(philo->id + 1) % philo->data->num]->taken)
		{
			pthread_mutex_lock(
				&philo->fork[(philo->id + 1) % philo->data->num]->mutex);
			philo->fork[(philo->id + 1) % philo->data->num]->taken = true;
			break ;
		}
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
