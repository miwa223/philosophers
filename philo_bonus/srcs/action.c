#include "philo_bonus.h"
#include "utils.h"

long	take_forks(t_thread *philo)
{
	long	time;

	sem_wait(philo->monitor->sem_fork);
	print_log(philo, "has taken a fork");
	time = print_log(philo, "has taken a fork");
	if (time == 0)
	{
		sem_post(philo->monitor->sem_fork);
		return (0);
	}
	if (is_dead(philo))
		return (0);
	return (time);
}

bool	eating(t_thread *philo, long start_time)
{
	philo->prev_eat_time = print_log(philo, "is eating");
	sleep_loop_usec(philo->data->eat_usec, start_time);
	philo->eat_count += 1;
	sem_post(philo->monitor->sem_fork);
	if (philo->data->eat_times != -1
		&& philo->eat_count >= philo->data->eat_times)
		sem_post(philo->monitor->sem_count);
	if (is_dead(philo))
		return (false);
	return (true);
}

bool	sleeping(t_thread *philo)
{
	long	start_time;

	start_time = print_log(philo, "is sleeping");
	sleep_loop_usec(philo->data->sleep_usec, start_time);
	if (is_dead(philo))
		return (false);
	return (true);
}

bool	thinking(t_thread *philo)
{
	return (print_log(philo, "is thinking"));
}

void	*action(void *philo_thread)
{
	t_thread	*philo;
	long		start_time;

	philo = (t_thread *)philo_thread;
	if (philo->id % 2 == 1)
		usleep(1000);
	while (!is_dead(philo))
	{
		start_time = take_forks(philo);
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
