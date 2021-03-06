/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:01:24 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/05/03 17:22:10 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

void	init_data(char **argv, t_data *data)
{
	data->num = ft_atoi(argv[1], NULL);
	data->die_usec = (unsigned int)ft_atoi(argv[2], NULL) * 1000;
	data->eat_usec = (unsigned int)ft_atoi(argv[3], NULL) * 1000;
	data->sleep_usec = (unsigned int)ft_atoi(argv[4], NULL) * 1000;
	if (argv[5] != NULL)
		data->eat_times = ft_atoi(argv[5], NULL);
	else
		data->eat_times = -1;
}

t_fork	**init_fork(t_data *data)
{
	int		i;
	t_fork	**fork;

	i = 0;
	fork = malloc(sizeof(t_fork *) * (data->num + 1));
	if (fork == NULL)
		return (NULL);
	while (i < data->num)
	{
		fork[i] = malloc(sizeof(t_fork));
		if (fork[i] == NULL)
			return (free_contents(fork, NULL, NULL));
		fork[i]->is_taken = false;
		pthread_mutex_init(&fork[i]->mutex, NULL);
		i++;
	}
	fork[i] = NULL;
	return (fork);
}

t_monitor	*init_monitor(void)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)malloc(sizeof(t_monitor));
	if (monitor == NULL)
		return (NULL);
	monitor->end = false;
	pthread_mutex_init(&monitor->mutex, NULL);
	return (monitor);
}

t_thread	**init_philo_content(
	t_data *data, t_fork **fork, t_monitor *monitor)
{
	int			i;
	t_thread	**philo;

	i = 0;
	philo = malloc(sizeof(t_thread *) * (data->num + 1));
	if (philo == NULL)
		return (free_contents(fork, monitor, NULL));
	while (i < data->num)
	{
		philo[i] = (t_thread *)malloc(sizeof(t_thread));
		if (philo[i] == NULL)
			return (free_contents(fork, monitor, philo));
		philo[i]->id = i;
		philo[i]->data = data;
		philo[i]->fork = fork;
		philo[i]->left_fork_id = (i + 1) % data->num;
		philo[i]->prev_eat_time = get_usec();
		pthread_mutex_init(&philo[i]->mutex_time, NULL);
		philo[i]->eat_count = 0;
		pthread_mutex_init(&philo[i]->mutex_count, NULL);
		philo[i]->monitor = monitor;
		i++;
	}
	philo[i] = NULL;
	return (philo);
}

t_thread	**init_philo(t_data *data)
{
	t_fork		**fork;
	t_monitor	*monitor;

	fork = init_fork(data);
	if (fork == NULL)
		return (NULL);
	monitor = init_monitor();
	if (monitor == NULL)
		return (free_contents(fork, NULL, NULL));
	return (init_philo_content(data, fork, monitor));
}
