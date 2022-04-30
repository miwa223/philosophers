/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_usec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc  <mmasubuc@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 23:43:50 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/04/28 17:56:34 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

long	get_usec(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return (tv.tv_sec * 1000 * 1000 + tv.tv_usec);
}

void	sleep_loop_usec(unsigned int need_to_sleep_usec, long past_time_usec)
{
	while (get_usec() - past_time_usec < need_to_sleep_usec)
		usleep(200);
}
