#include "philo.h"
#include "utils.h"

bool	someone_died(t_thread *philo, int i)
{
	if (get_time() - philo->prev_eat_time > philo->data->die_t)
	{
		philo->monitor->end = true;
		printf("%ld %d died\n", get_time(), i + 1);
		return (true);
	}
	return (false);
}

void	*monitor(void *philo_thread)
{
	t_thread	**philo;
	int			i;
	int			count;

	philo = (t_thread **)philo_thread;
	while (!philo[0]->monitor->end)
	{
		i = 0;
		count = 0;
		while (philo[i])
		{
			if (someone_died(philo[i], i))
				return (NULL);
			if (philo[i]->eat_done)
				count++;
			i++;
		}
		if (count == philo[0]->data->num)
			break ;
		usleep(50);
	}
	return (NULL);
}
