#include "philo_bonus.h"

sem_t	*open_a_semaphore(char *str, int num)
{
	sem_t	*sem;

	sem_unlink(str);
	sem = sem_open(str, O_CREAT, S_IWUSR | S_IRUSR, num);
	if (sem == SEM_FAILED)
		printf("Errno: %d: Error while sem_open\n", errno);
	return (sem);
}

void	*open_semaphores(t_data *data, t_monitor *monitor)
{
	monitor->sem_fork = open_a_semaphore(SEM_FORK, data->num);
	if (monitor->sem_fork == SEM_FAILED)
		return (free_contents(monitor, NULL, 1));
	monitor->sem_time = open_a_semaphore(SEM_EAT_TIME, 1);
	if (monitor->sem_time == SEM_FAILED)
		return (free_contents(monitor, NULL, 2));
	monitor->sem_count = open_a_semaphore(SEM_EAT_COUNT, 1);
	if (monitor->sem_count == SEM_FAILED)
		return (free_contents(monitor, NULL, 3));
	monitor->sem_end = open_a_semaphore(SEM_END, 1);
	if (monitor->sem_end == SEM_FAILED)
		return (free_contents(monitor, NULL, NUM_OF_SEM));
	return (monitor);
}
