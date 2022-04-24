#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	eating(t_thread *philo)
{
	long	eat_time;
	long	diff;

	take_right_fork(philo);
	printf("%ld %d has taken a fork\n", get_time(), philo->id + 1);
	take_left_fork(philo);
	eat_time = get_time();
	printf("%ld %d has taken a fork\n", eat_time, philo->id + 1);
	printf("%ld %d is eating\n", eat_time, philo->id + 1);
	philo->prev_eat_time = eat_time;
	diff = get_time() - eat_time;
	usleep(philo->data->eat_t - diff);
	put_back_forks(philo);
}

void	sleeping(t_thread *philo)
{
	long	now;

	now = get_time();
	printf("%ld %d is sleeping\n", now, philo->id + 1);
	usleep(philo->data->sleep_t - (now - philo->prev_eat_time));
}

void	thinking(t_thread *philo)
{
	printf("%ld %d is thinking\n", get_time(), philo->id + 1);
}

void	*action(void *philo)
{
	t_thread	*philo_cp;

	philo_cp = (t_thread *)philo;
	if (philo_cp->id % 2 == 1)
		usleep(200);
	while (1)
	{
		eating(philo_cp);
		sleeping(philo_cp);
		thinking(philo_cp);
	}
	return (NULL);
}
