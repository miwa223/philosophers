#include "philo.h"
#include "utils.h"

void	destroy_fork_mutexes(t_thread *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num)
	{
		pthread_mutex_unlock(&philo->fork[i]->mutex);
		pthread_mutex_destroy(&philo->fork[i]->mutex);
		i++;
	}
}

bool	is_valid_argv(int argc, char **argv)
{
	int		i;
	size_t	j;
	int		overflow;
	int		num;

	i = 1;
	if (argc < 5 || argc > 6)
		return (false);
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] && ft_isdigit(argv[i][j]) == 1)
			j++;
		if (ft_strlen(argv[i]) != j)
			return (false);
		num = ft_atoi(argv[i], &overflow);
		if ((i != 1 && i != 5) && (num <= 0 || num > USEC_T_MAX || overflow))
			return (false);
		else if ((i == 1 || i == 5) && (num <= 0 || overflow))
			return (false);
		i++;
	}
	return (true);
}

int	exit_program(int type)
{
	(void)type;
	printf("Error detected while simulation.\n");
	return (1);
}

int	philosopher(t_thread **philo)
{
	int	i;

	i = 0;
	while (i < philo[0]->data->num)
	{
		if (pthread_create(&philo[i]->tid, NULL, action, philo[i]) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < philo[0]->data->num)
	{
		if (pthread_join(philo[i]->tid, NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

void	free_contents(t_thread **philo)
{
	int	i;
	int	num_of_philo;

	i = 0;
	num_of_philo = philo[0]->data->num;
	while (i < num_of_philo)
	{
		pthread_mutex_unlock(&philo[i]->fork[i]->mutex);
		pthread_mutex_destroy(&philo[i]->fork[i]->mutex);
		free(philo[i]->fork[i]);
		i++;
	}
	free(philo[0]->monitor);
	free(philo[0]->fork);
	i = 0;
	while (i < num_of_philo)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_thread	**philo;

	if (!is_valid_argv(argc, argv))
		exit_program(ARG);
	init_data(argv, &data);
	philo = init_philo(&data);
	if (philo == NULL)
		return (exit_program(MALLOC));
	if (pthread_create(&philo[0]->monitor->tid, NULL, monitor, philo[0]) != 0)
		return (exit_program(MONITOR));
	if (philosopher(philo) == 1)
		return (exit_program(PHILO));
	if (pthread_join(philo[0]->monitor->tid, NULL) != 0)
		return (exit_program(MONITOR));
	free_contents(philo);
	return (0);
}
