/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_operation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 20:13:38 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/05/03 17:30:29 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

long	take_a_fork(t_thread *philo, int num)
{
	long	time;

	pthread_mutex_lock(&philo->fork[num]->mutex);
	time = print_log(philo, "has taken a fork");
	if (time == 0)
	{
		if (num != philo->id)
		{
			philo->fork[philo->id]->is_taken = false;
			pthread_mutex_unlock(&philo->fork[philo->id]->mutex);
			pthread_mutex_unlock(&philo->fork[num]->mutex);
		}
		else
			pthread_mutex_unlock(&philo->fork[num]->mutex);
		return (0);
	}
	if (philo->data->num == 1)
	{
		pthread_mutex_unlock(&philo->fork[num]->mutex);
		return (0);
	}
	philo->fork[num]->is_taken = true;
	return (time);
}

void	put_back_forks(t_thread *philo)
{
	philo->fork[philo->id]->is_taken = false;
	pthread_mutex_unlock(&philo->fork[philo->id]->mutex);
	philo->fork[philo->left_fork_id]->is_taken = false;
	pthread_mutex_unlock(
		&philo->fork[philo->left_fork_id]->mutex);
}
