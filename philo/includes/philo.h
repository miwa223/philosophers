#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define USEC_T_MAX 1000000

typedef enum e_error
{
	ARG,
	MALLOC,
	MONITOR,
	PHILO,
}				t_error;

typedef struct s_data
{
	int				num;
	unsigned int	die_t;
	unsigned int	eat_t;
	unsigned int	sleep_t;
	int				eat_times;
}				t_data;

typedef struct s_fork
{
	bool			taken;
	pthread_mutex_t	mutex;
}				t_fork;

typedef struct s_monitor
{
	pthread_t	tid;
	bool		dead;
	int			dead_philo;
	bool		already_dead;
}				t_monitor;

typedef struct s_thread
{
	int			id;
	pthread_t	tid;
	t_data		*data;
	t_fork		**fork;
	long		prev_eat_time;
	int			eaten_cnt;
	t_monitor	*monitor;
}				t_thread;

int			philosopher(t_thread **philo);
void		init_data(char **argv, t_data *data);
t_fork		**init_fork(t_data *data);
t_thread	**init_philo(t_data *data);

void		*action(void *philo);
void		eating(t_thread *philo);
void		sleeping(t_thread *philo);
void		thinking(t_thread *philo);

void		take_right_fork(t_thread *philo);
void		take_left_fork(t_thread *philo);
void		put_back_forks(t_thread *philo);

void		*monitor(void *philo_thread);

#endif
