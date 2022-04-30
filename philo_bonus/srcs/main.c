#include "philo_bonus.h"

void	exec_philo(t_thread **philo, int i)
{
	if (pthread_create(&philo[i]->monitor->tid, NULL, monitor, philo[i])
		|| pthread_create(&philo[i]->tid, NULL, action, philo[i])
		|| pthread_detach(philo[i]->tid)
		|| pthread_join(philo[i]->monitor->tid, NULL))
	{
		pthread_detach(philo[i]->tid);
		pthread_detach(philo[i]->monitor->tid);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

int	*create_processes_and_threads(t_thread **philo)
{
	int	*pid;
	int	i;

	i = 0;
	pid = malloc(sizeof(int) * philo[0]->data->num);
	if (pid == NULL)
		return (NULL);
	while (i < philo[0]->data->num)
	{
		pid[i] = fork();
		if (pid[i] == -1)
		{
			error_handling(FORK, philo, pid);
			kill(0, SIGINT);
		}
		if (pid[i] == 0)
			exec_philo(philo, i);
		i++;
	}
	return (pid);
}

void	wait_child(int *pid, t_thread **philo)
{
	int	i;
	int	wstatus;
	int	res;

	i = 0;
	res = waitpid(-1, &wstatus, 0);
	if (res == -1)
	{
		error_handling(WAITING, philo, pid);
		kill(0, SIGINT);
	}
	while (i < philo[0]->data->num)
	{
		kill(pid[i], SIGINT);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_thread	**philo;
	int			*pid;

	if (!is_valid_argv(argc, argv))
		return (error_handling(ARG, NULL, NULL));
	init_data(argv, &data);
	philo = init_philo(&data);
	if (philo == NULL)
		return (error_handling(INIT, NULL, NULL));
	pid = create_processes_and_threads(philo);
	wait_child(pid, philo);
	free(pid);
	free_contents(philo[0]->monitor, philo, NUM_OF_SEM);
	return (0);
}
