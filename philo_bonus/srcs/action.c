#include "philo_bonus.h"
#include "utils.h"

long	take_forks(t_thread *philo)
{
	long	time;

	sem_wait(philo->monitor->sem_fork);
	print_log(philo, "has taken a fork");
	sem_wait(philo->monitor->sem_fork);
	time = print_log(philo, "has taken a fork");
	if (time == 0 || philo->data->num == 1)
	{
		sem_post(philo->monitor->sem_fork);
		return (0);
	}
	return (time);
}

bool	eating(t_thread *philo, long start_time)
{
	long	eat_time;

	eat_time = print_log(philo, "is eating");
	if (eat_time == 0)
		return (false);
	sem_wait(philo->monitor->sem_time);
	philo->prev_eat_time = eat_time;
	sem_post(philo->monitor->sem_time);
	sleep_loop_usec(philo->data->eat_usec, start_time);
	sem_wait(philo->monitor->sem_count);
	philo->eat_count += 1;
	sem_post(philo->monitor->sem_count);
	sem_post(philo->monitor->sem_fork);
	sem_post(philo->monitor->sem_fork);
	return (true);
}

bool	sleeping(t_thread *philo)
{
	long	start_time;

	start_time = print_log(philo, "is sleeping");
	if (start_time == 0)
		return (false);
	sleep_loop_usec(philo->data->sleep_usec, start_time);
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
	while (1)
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
