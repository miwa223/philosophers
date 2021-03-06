/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 10:07:44 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/05/03 17:19:42 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*free_fork(t_fork **fork)
{
	int	i;

	i = 0;
	while (fork[i])
	{
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
	{
		pthread_mutex_destroy(&philo[0]->monitor->mutex);
		free(monitor);
	}
	if (philo)
	{
		while (philo[i])
		{
			pthread_mutex_destroy(&philo[i]->mutex_time);
			pthread_mutex_destroy(&philo[i]->mutex_count);
			free(philo[i]);
			i++;
		}
		free(philo);
	}
	return (NULL);
}
