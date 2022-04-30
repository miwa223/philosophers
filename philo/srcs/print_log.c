/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc  <mmasubuc@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 20:17:04 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/04/28 20:32:02 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

long	print_log(t_thread *philo, char *msg)
{
	long	now;

	pthread_mutex_lock(&philo->monitor->mutex);
	if (philo->monitor->end)
	{
		pthread_mutex_unlock(&philo->monitor->mutex);
		return (0);
	}
	now = get_usec();
	printf("%ld %d %s\n", now / 1000, philo->id + 1, msg);
	pthread_mutex_unlock(&philo->monitor->mutex);
	return (now);
}
