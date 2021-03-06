/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:27:26 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/05/05 09:40:23 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

bool	is_valid_argv(int argc, char **argv)
{
	int		i;
	int		overflow;
	int		num;

	i = 1;
	if (argc < 5 || argc > 6)
		return (false);
	while (i < argc)
	{
		if (!is_digit(argv, i))
			return (false);
		num = ft_atoi(argv[i], &overflow);
		if (overflow || num <= 0)
			return (false);
		if (i == 1 && num > THREAD_MAX - 2)
			return (false);
		if ((1 < i && i < 5) && (unsigned int)num > UINT_MAX / 1000)
			return (false);
		i++;
	}
	return (true);
}

int	exit_program(t_error type, t_thread **philo)
{
	if (type == ARG)
		printf("Invalid arguments.\n");
	else if (type == MALLOC)
		printf("Memory allocation failed.\n");
	else
	{
		if (type != MONITOR_CREATE)
			pthread_detach(philo[0]->monitor->tid);
		free_contents(philo[0]->fork, philo[0]->monitor, philo);
		printf("Error detected while simulation.\n");
	}
	return (1);
}

int	philosopher(t_thread **philo)
{
	int	i;

	i = 0;
	while (i < philo[0]->data->num)
	{
		if (pthread_create(&philo[i]->tid, NULL, action, philo[i]))
		{
			while (i-- > 0)
				pthread_detach(philo[i]->tid);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < philo[0]->data->num)
	{
		if (pthread_join(philo[i]->tid, NULL))
		{
			while (i < philo[0]->data->num)
				pthread_detach(philo[i++]->tid);
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_thread	**philo;

	if (!is_valid_argv(argc, argv))
		return (exit_program(ARG, NULL));
	init_data(argv, &data);
	philo = init_philo(&data);
	if (philo == NULL)
		return (exit_program(MALLOC, NULL));
	if (pthread_create(&philo[0]->monitor->tid, NULL, monitor, philo) != 0)
		return (exit_program(MONITOR_CREATE, philo));
	if (philosopher(philo) == 1)
		return (exit_program(PHILO, philo));
	if (pthread_join(philo[0]->monitor->tid, NULL) != 0)
		return (exit_program(MONITOR_JOIN, philo));
	free_contents(philo[0]->fork, philo[0]->monitor, philo);
	return (0);
}
