/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc  <mmasubuc@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 16:52:59 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/04/30 23:15:49 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "utils.h"

void	init_data(char **argv, t_data *data)
{
	int		i;

	i = 0;
	data->num = ft_atoi(argv[1], NULL);
	data->die_usec = (unsigned int)ft_atoi(argv[2], NULL) * 1000;
	data->eat_usec = (unsigned int)ft_atoi(argv[3], NULL) * 1000;
	data->sleep_usec = (unsigned int)ft_atoi(argv[4], NULL) * 1000;
	if (argv[5] != NULL)
		data->eat_times = ft_atoi(argv[5], NULL);
	else
		data->eat_times = -1;
}

t_monitor	*init_monitor(void)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)malloc(sizeof(t_monitor));
	if (monitor == NULL)
		return (NULL);
	return (monitor);
}

t_thread	**init_philo_content(t_data *data, t_monitor *monitor)
{
	int			i;
	t_thread	**philo;

	i = 0;
	philo = malloc(sizeof(t_thread *) * (data->num + 1));
	if (philo == NULL)
		return (free_contents(monitor, NULL, NUM_OF_SEM));
	while (i < data->num)
	{
		philo[i] = (t_thread *)malloc(sizeof(t_thread));
		if (philo[i] == NULL)
			return (free_contents(monitor, philo, NUM_OF_SEM));
		philo[i]->id = i;
		philo[i]->data = data;
		philo[i]->prev_eat_time = get_usec();
		philo[i]->eat_count = 0;
		philo[i]->monitor = monitor;
		i++;
	}
	philo[i] = NULL;
	return (philo);
}

t_thread	**init_philo(t_data *data)
{
	t_monitor	*monitor;

	monitor = init_monitor();
	if (monitor == NULL)
		return (NULL);
	if (init_semaphores(data, monitor) == NULL)
		return (NULL);
	return (init_philo_content(data, monitor));
}
