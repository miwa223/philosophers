/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:58:23 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/05/03 17:31:40 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

bool	eating(t_thread *philo, long start_time)
{
	long	eat_time;

	eat_time = print_log(philo, "is eating");
	if (eat_time == 0)
	{
		put_back_forks(philo);
		return (false);
	}
	pthread_mutex_lock(&philo->mutex_time);
	philo->prev_eat_time = eat_time;
	pthread_mutex_unlock(&philo->mutex_time);
	sleep_loop_usec(philo->data->eat_usec, start_time);
	pthread_mutex_lock(&philo->mutex_count);
	philo->eat_count += 1;
	pthread_mutex_unlock(&philo->mutex_count);
	put_back_forks(philo);
	return (true);
}

bool	sleeping(t_thread *philo)
{
	long	start_time;

	start_time = print_log(philo, "is sleeping");
	if (start_time == 0)
		return (false);
	sleep_loop_usec(philo->data->sleep_usec, start_time);
	return (true);
}

bool	thinking(t_thread *philo)
{
	return (print_log(philo, "is thinking"));
}

void	*action(void *philo_thread)
{
	t_thread	*philo;
	long		start_time;

	philo = (t_thread *)philo_thread;
	if (philo->id % 2 == 1)
		usleep(1000);
	while (1)
	{
		if (!take_a_fork(philo, philo->id))
			break ;
		start_time = take_a_fork(philo, philo->left_fork_id);
		if (start_time == 0)
			break ;
		if (!eating(philo, start_time))
			break ;
		if (!sleeping(philo))
			break ;
		if (!thinking(philo))
			break ;
	}
	return (NULL);
}
