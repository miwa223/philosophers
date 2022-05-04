/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 19:22:21 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/05/04 00:28:56 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	delete_sems(t_monitor *monitor, int id)
{
	if (id > 0)
	{
		sem_close(monitor->sem_fork);
		if (sem_unlink(SEM_FORK))
			printf("Errno: %d: Error while sem_unlink.\n", errno);
	}
	if (id > 1)
	{
		sem_close(monitor->sem_count);
		if (sem_unlink(SEM_EAT_COUNT))
			printf("Errno: %d: Error while sem_unlink.\n", errno);
	}
	if (id > 2)
	{
		sem_close(monitor->sem_time);
		if (sem_unlink(SEM_EAT_TIME))
			printf("Errno: %d: Error while sem_unlink.\n", errno);
	}
	if (id > 3)
	{
		sem_close(monitor->sem_end);
		if (sem_unlink(SEM_END))
			printf("Errno: %d: Error while sem_unlink.\n", errno);
	}
}

void	*free_contents(t_monitor *monitor, t_thread **philo, int num)
{
	int	i;

	i = 0;
	if (monitor)
	{
		delete_sems(monitor, num);
		free(monitor);
	}
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
