#include "philo.h"
#include "utils.h"

int	destroy_fork_mutexes(t_thread *philo)
{
	int	i;

	i = 0;
	while (i < philo->data->num)
	{
		if (pthread_mutex_destroy(&philo->fork[i]->mutex) != 0)
			return (-1);
		i++;
	}
	return (0);
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

void	exit_program(int status)
{
	if (status == ERROR)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}

int	philosopher(t_thread **philo)
{
	int	i;

	i = 0;
	while (i < philo[0]->data->num)
	{
		if (pthread_create(&philo[i]->tid, NULL, action, philo[i]) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < philo[0]->data->num)
	{
		if (pthread_join(philo[i]->tid, NULL) != 0)
			exit(EXIT_FAILURE);
		i++;
	}
	destroy_fork_mutexes(philo[0]);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_thread	**philo;

	if (!is_valid_argv(argc, argv))
		exit_program(ERROR);
	init_data(argv, &data);
	philo = init_philo(&data);
	if (philo == NULL)
		return (-1);
	if (philosopher(philo) == -1)
		exit_program(ERROR);
	return (0);
}
