/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc <mmasubuc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 01:37:48 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/05/04 21:17:07 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <errno.h>

# define SEM_FORK "/forks"
# define SEM_EAT_TIME "/eat_time"
# define SEM_EAT_COUNT "/eat_counts"
# define SEM_END "/ends"
# define NUM_OF_SEM 4
# define PROCESS_MAX 709

typedef enum e_error
{
	ARG,
	INIT,
	FORK,
	WAITING,
}				t_error;

typedef struct s_data
{
	int				num;
	unsigned int	die_usec;
	unsigned int	eat_usec;
	unsigned int	sleep_usec;
	int				eat_times;
}				t_data;

typedef struct s_monitor
{
	pthread_t	tid;
	sem_t		*sem_fork;
	sem_t		*sem_count;
	sem_t		*sem_time;
	sem_t		*sem_end;
}				t_monitor;

typedef struct s_thread
{
	int			id;
	pthread_t	tid;
	t_data		*data;
	long		prev_eat_time;
	int			eat_count;
	t_monitor	*monitor;
}				t_thread;

bool		is_valid_argv(int argc, char **argv);
int			*create_processes_and_threads(t_thread **philo);
void		check_philos_eat_done(t_thread *philo);
void		exec_philo(t_thread **philo, int i);
void		wait_child(int *pid, t_thread **philo);

t_thread	**init_philo(t_data *data);
t_thread	**init_philo_content(t_data *data, t_monitor *monitor);
void		init_data(char **argv, t_data *data);
t_monitor	*init_monitor(void);
void		*init_semaphores(t_data *data, t_monitor *monitor);
sem_t		*open_a_semaphore(char *str, int num);

void		*action(void *philo_thread);
long		take_forks(t_thread *philo);
void		eating(t_thread *philo, long start_time);
void		sleeping(t_thread *philo);
void		thinking(t_thread *philo);

bool		is_dead(t_thread *philo);
long		print_log(t_thread *philo, char *msg);

void		*monitor(void *philo_thread);

void		*free_contents(t_monitor *monitor, t_thread **philo, int num);
void		delete_sems(t_monitor *monitor, int id);
int			error_handling(int type, t_thread **philo, int *pid);

#endif
