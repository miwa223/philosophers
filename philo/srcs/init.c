#include "philo.h"
#include "utils.h"

void	init_data(char **argv, t_data *data)
{
	int		i;

	i = 0;
	data->num = ft_atoi(argv[1], NULL);
	data->die_t = (unsigned int)ft_atoi(argv[2], NULL) * 1000;
	data->eat_t = (unsigned int)ft_atoi(argv[3], NULL) * 1000;
	data->sleep_t = (unsigned int)ft_atoi(argv[4], NULL) * 1000;
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
	fork = malloc(sizeof(t_fork *) * data->num);
	if (fork == NULL)
		return (NULL);
	while (i < data->num)
	{
		fork[i] = malloc(sizeof(t_fork));
		if (fork[i] == NULL)
			return (NULL);
		fork[i]->taken = false;
		pthread_mutex_init(&fork[i]->mutex, NULL);
		i++;
	}
	return (fork);
}

t_thread	**init_philo(t_data *data)
{
	int			i;
	t_fork		**fork;
	t_thread	**philo;

	i = 0;
	fork = init_fork(data);
	if (fork == NULL)
		return (NULL);
	philo = malloc(sizeof(t_thread *) * (data->num));
	if (philo == NULL)
		return (NULL);
	while (i < data->num)
	{
		philo[i] = (t_thread *)malloc(sizeof(t_thread));
		if (philo[i] == NULL)
			return (NULL);
		philo[i]->id = i;
		philo[i]->data = data;
		philo[i]->fork = fork;
		i++;
	}
	return (philo);
}
