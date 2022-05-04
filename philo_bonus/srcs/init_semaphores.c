/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_semaphores.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 17:12:10 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/05/04 00:28:34 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

sem_t	*open_a_semaphore(char *str, int num)
{
	sem_t	*sem;

	sem_unlink(str);
	sem = sem_open(str, O_CREAT, S_IWUSR | S_IRUSR, num);
	if (sem == SEM_FAILED)
		printf("Errno: %d: Error while sem_open\n", errno);
	return (sem);
}

void	*init_semaphores(t_data *data, t_monitor *monitor)
{
	monitor->sem_fork = open_a_semaphore(SEM_FORK, data->num / 2);
	if (monitor->sem_fork == SEM_FAILED)
		return (free_contents(monitor, NULL, 0));
	monitor->sem_count = open_a_semaphore(SEM_EAT_COUNT, 0);
	if (monitor->sem_count == SEM_FAILED)
		return (free_contents(monitor, NULL, 1));
	monitor->sem_time = open_a_semaphore(SEM_EAT_TIME, 1);
	if (monitor->sem_time == SEM_FAILED)
		return (free_contents(monitor, NULL, 2));
	monitor->sem_end = open_a_semaphore(SEM_END, 1);
	if (monitor->sem_end == SEM_FAILED)
		return (free_contents(monitor, NULL, 3));
	return (monitor);
}
