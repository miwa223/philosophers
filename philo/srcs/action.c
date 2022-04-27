#include "philo.h"
#include "utils.h"

void	eating(t_thread *philo)
{
	long	eat_time;

	take_a_fork(check_fork_is_remaining, philo, philo->id);
	take_a_fork(
		check_fork_is_remaining, philo, (philo->id + 1) % philo->data->num);
	eat_time = get_time();
	if (!is_end(philo))
		printf("%ld %d is eating\n", eat_time, philo->id + 1);
	pthread_mutex_lock(&philo->mutex_time);
	philo->prev_eat_time = eat_time;
	pthread_mutex_unlock(&philo->mutex_time);
	sleep_loop(philo->data->eat_t, eat_time);
	pthread_mutex_lock(&philo->mutex_count);
	philo->eat_count += 1;
	pthread_mutex_unlock(&philo->mutex_count);
	put_back_forks(philo);
}

void	sleeping(t_thread *philo)
{
	long	now;

	now = get_time();
	printf("%ld %d is sleeping\n", now, philo->id + 1);
	sleep_loop(philo->data->sleep_t, now);
}

void	thinking(t_thread *philo)
{
	printf("%ld %d is thinking\n", get_time(), philo->id + 1);
}

void	*action(void *philo_thread)
{
	t_thread	*philo;

	philo = (t_thread *)philo_thread;
	if (philo->id % 2 == 1)
		usleep(200);
	while (!is_end(philo))
	{
		eating(philo);
		if (is_end(philo))
			break ;
		sleeping(philo);
		if (is_end(philo))
			break ;
		thinking(philo);
	}
	return (NULL);
}
