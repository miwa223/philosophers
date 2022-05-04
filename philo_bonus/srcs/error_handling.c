/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:35:11 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/05/05 08:11:21 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
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
		if (i == 1 && num > PROCESS_MAX - 1)
			return (false);
		if ((1 < i && i < 5) && (unsigned int)num > UINT_MAX / 1000)
			return (false);
		i++;
	}
	return (true);
}

int	error_handling(t_error type, t_thread **philo, int *pid)
{
	if (type == ARG)
		printf("Invalid arguments.\n");
	else if (type == INIT)
		printf("Data initialization failed.\n");
	else if (type == MALLOC)
	{
		free_contents(philo[0]->monitor, philo, NUM_OF_SEM);
		printf("Memory allocation failed.\n");
	}
	else
	{
		free(pid);
		free_contents(philo[0]->monitor, philo, NUM_OF_SEM);
		if (type == FORK)
			printf("Creating child process failed.\n");
		else
			printf("Error detected while waiting child process termination.\n");
	}
	return (1);
}
