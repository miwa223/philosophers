/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 23:55:57 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/05/04 21:15:52 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "utils.h"

long	take_forks(t_thread *philo)
{
	long	time;

	sem_wait(philo->monitor->sem_fork);
	print_log(philo, "has taken a fork");
	time = print_log(philo, "has taken a fork");
	return (time);
}

void	eating(t_thread *philo, long start_time)
{
	long	eat_time;

	eat_time = print_log(philo, "is eating");
	sem_wait(philo->monitor->sem_time);
	philo->prev_eat_time = eat_time;
	sem_post(philo->monitor->sem_time);
	sleep_loop_usec(philo->data->eat_usec, start_time);
	philo->eat_count += 1;
	sem_post(philo->monitor->sem_fork);
	if (philo->data->eat_times != -1
		&& philo->eat_count == philo->data->eat_times)
		sem_post(philo->monitor->sem_count);
}

void	sleeping(t_thread *philo)
{
	long	start_time;

	start_time = print_log(philo, "is sleeping");
	sleep_loop_usec(philo->data->sleep_usec, start_time);
}

void	thinking(t_thread *philo)
{
	print_log(philo, "is thinking");
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
		start_time = take_forks(philo);
		eating(philo, start_time);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}
