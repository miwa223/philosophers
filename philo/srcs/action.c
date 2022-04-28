#include "philo.h"
#include "utils.h"

long	print_msg(t_thread *philo, char *str)
{
	long	now;

	pthread_mutex_lock(&philo->monitor->mutex);
	if (philo->monitor->end)
	{
		pthread_mutex_unlock(&philo->monitor->mutex);
		return (0);
	}
	now = get_usec();
	printf("%ld %d %s\n", now / 1000, philo->id + 1, str);
	pthread_mutex_unlock(&philo->monitor->mutex);
	return (now);
}

bool	eating(t_thread *philo, long start_time)
{
	long	eat_time;

	eat_time = print_msg(philo, "is eating");
	if (eat_time == 0)
		return (false);
	pthread_mutex_lock(&philo->mutex_time);
	philo->prev_eat_time = eat_time;
	pthread_mutex_unlock(&philo->mutex_time);
	sleep_loop_usec(philo->data->eat_usec, start_time);
	pthread_mutex_lock(&philo->mutex_count);
	philo->eat_count += 1;
	pthread_mutex_unlock(&philo->mutex_count);
	put_back_forks(philo);
	return (true);
}

bool	sleeping(t_thread *philo)
{
	long	start_time;

	start_time = print_msg(philo, "is sleeping");
	if (start_time == 0)
		return (false);
	sleep_loop_usec(philo->data->sleep_usec, start_time); //forkおろす時からにしたほうがいいかも
	return (true);
}

bool	thinking(t_thread *philo)
{
	return (print_msg(philo, "is thinking"));
}

void	*action(void *philo_thread)
{
	t_thread	*philo;
	long		start_time;

	philo = (t_thread *)philo_thread;
	if (philo->id % 2 == 1)
		usleep(1000);
	while (1)
	{
		if (!take_a_fork(philo, philo->id))
			break ;
		start_time = take_a_fork(philo, philo->left_fork_id);
		if (start_time == 0)
			break ;
		if (!eating(philo, start_time))
			break ;
		if (!sleeping(philo))
			break ;
		if (!thinking(philo))
			break ;
	}
	return (NULL);
}
