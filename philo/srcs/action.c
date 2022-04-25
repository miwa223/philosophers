#include "philo.h"
#include "utils.h"

void	eating(t_thread *philo)
{
	long	eat_time;

	take_right_fork(philo);
	printf("%zu %d has taken a fork\n", get_time(), philo->id + 1);
	if (philo->monitor->end)
		return ;
	take_left_fork(philo);
	eat_time = get_time();
	printf("%zu %d has taken a fork\n", eat_time, philo->id + 1);
	if (philo->monitor->end
		|| eat_time - philo->prev_eat_time >= philo->data->die_t)
	{
		philo->monitor->end = true;
		if (philo->monitor->dead_philo == 0)
			philo->monitor->dead_philo = philo->id;
		return ;
	}
	printf("%zu %d is eating\n", eat_time, philo->id + 1);
	philo->prev_eat_time = eat_time;
	usleep(philo->data->eat_t - (get_time() - eat_time));
	philo->eaten_cnt += 1;
	put_back_forks(philo);
}

void	sleeping(t_thread *philo)
{
	long	now;

	now = get_time();
	printf("%zu %d is sleeping\n", now, philo->id + 1);
	usleep(philo->data->sleep_t - (now - philo->prev_eat_time));
}

void	thinking(t_thread *philo)
{
	printf("%zu %d is thinking\n", get_time(), philo->id + 1);
}

void	operate_for_first_dead(t_thread *philo)
{
	if (!philo->monitor->already_dead)
	{
		philo->monitor->already_dead = true;
		usleep(50);
		printf("%zu %d died\n",
			get_time(), philo->monitor->dead_philo + 1);
	}
}

void	*action(void *philo)
{
	t_thread	*philo_cp;

	philo_cp = (t_thread *)philo;
	philo_cp->prev_eat_time = get_time();
	if (philo_cp->id % 2 == 1)
		usleep(200);
	while (!philo_cp->monitor->end)
	{
		eating(philo_cp);
		if (philo_cp->eaten_cnt == philo_cp->data->eat_times)
		{
			philo_cp->monitor->end = true;
			break ;
		}
		if (philo_cp->monitor->end)
		{
			operate_for_first_dead(philo_cp);
			break ;
		}
		sleeping(philo_cp);
		if (philo_cp->monitor->end)
			break ;
		thinking(philo_cp);
	}
	return (NULL);
}
