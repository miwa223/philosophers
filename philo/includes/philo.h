/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmasubuc  <mmasubuc@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 00:16:15 by mmasubuc          #+#    #+#             */
/*   Updated: 2022/04/28 20:32:02 by mmasubuc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define THREAD_MAX 512

typedef enum e_error
{
	ARG,
	MALLOC,
	MONITOR_CREATE,
	MONITOR_JOIN,
	PHILO,
}				t_error;

typedef struct s_data
{
	int				num;
	unsigned int	die_usec;
	unsigned int	eat_usec;
	unsigned int	sleep_usec;
	int				eat_times;
}				t_data;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct s_monitor
{
	pthread_t		tid;
	bool			end;
	pthread_mutex_t	mutex;
}				t_monitor;

typedef struct s_thread
{
	int				id;
	pthread_t		tid;
	t_data			*data;
	t_fork			**fork;
	int				left_fork_id;
	long			prev_eat_time;
	pthread_mutex_t	mutex_time;
	int				eat_count;
	pthread_mutex_t	mutex_count;
	t_monitor		*monitor;
}				t_thread;

int			philosopher(t_thread **philo);
bool		is_valid_argv(int argc, char **argv);
t_thread	**init_philo(t_data *data);
t_thread	**init_philo_content(
				t_data *data, t_fork **fork, t_monitor *monitor);
void		init_data(char **argv, t_data *data);
t_fork		**init_fork(t_data *data);
t_monitor	*init_monitor(void);

void		*action(void *philo_thread);
long		take_a_fork(t_thread *philo, int num);
bool		eating(t_thread *philo, long start_time);
void		put_back_forks(t_thread *philo);
bool		sleeping(t_thread *philo);
bool		thinking(t_thread *philo);

long		print_log(t_thread *philo, char *msg);

void		*monitor(void *philo_thread);
bool		someone_died(t_thread *philo, int i);
bool		ate_enough(t_thread *philo);
void		raise_end_flag(t_thread *philo);

void		*free_contents(t_fork **fork, t_monitor *monitor, t_thread **philo);
void		*free_fork(t_fork **fork);
int			exit_program(int type, t_thread **philo);

#endif
