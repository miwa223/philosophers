#include "philo.h"
#include "utils.h"

void	eating(t_thread *philo)
{
	long	eat_time;

	take_right_fork(philo);
	if (!philo->monitor->end)
		printf("%ld %d has taken a fork\n", get_time(), philo->id + 1);
	take_left_fork(philo);
	if (!philo->monitor->end)
		printf("%ld %d has taken a fork\n", get_time(), philo->id + 1);
	eat_time = get_time();
	if (!philo->monitor->end)
		printf("%ld %d is eating\n", eat_time, philo->id + 1);
	philo->prev_eat_time = eat_time;
	if (philo->monitor->end)
	{
		put_back_forks(philo);
		return ;
	}
	usleep(philo->data->eat_t - (get_time() - eat_time));
	philo->eaten_cnt += 1;
	put_back_forks(philo);
}

void	sleeping(t_thread *philo)
{
	if (!philo->monitor->end)
	{
		printf("%ld %d is sleeping\n", get_time(), philo->id + 1);
		usleep(philo->data->sleep_t - (get_time() - philo->prev_eat_time));
	}
}

void	thinking(t_thread *philo)
{
	if (!philo->monitor->end)
		printf("%ld %d is thinking\n", get_time(), philo->id + 1);
}

void	*action(void *philo)
{
	t_thread	*philo_cp;

	philo_cp = (t_thread *)philo;
	if (philo_cp->id % 2 == 1)
		usleep(200);
	while (!philo_cp->monitor->end)
	{
		eating(philo_cp);
		if (philo_cp->eaten_cnt == philo_cp->data->eat_times)
		{
			philo_cp->eat_done = true;
			break ;
		}
		if (!philo_cp->monitor->end)
			sleeping(philo_cp);
		if (!philo_cp->monitor->end)
			thinking(philo_cp);
	}
	return (NULL);
}
