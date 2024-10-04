/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:24:14 by karpatel          #+#    #+#             */
/*   Updated: 2024/08/24 16:24:16 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <pthread.h>
# include <limits.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_philo t_philo;

typedef enum e_index
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_index;

typedef enum e_time
{
	MILLISECONDS,
	MICROSECONDS,
}			t_time;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}				t_philo_status;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}				t_fork;

typedef struct s_info
{
	long			no_of_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			no_of_meals;
	long			start_time;
	bool			stop_program;
	bool			all_threads_ready;
	long			running_no_of_threads;
	pthread_mutex_t	info_mutex;
	pthread_mutex_t	write_lock;
	pthread_t		monitor;
	t_fork			*forks;
	t_philo			*philos;
}				t_info;

typedef struct s_philo
{
	int				id;
	int				no_of_meals_taken;
	bool			full;
	long			last_meal_time;
	t_fork			*first_fork;
	t_fork			*second_fork;
	pthread_mutex_t	philo_mutex;
	pthread_t		thread_id;
	t_info			*info;
}				t_philo;

// Input handling functions
int		checkargs(char *argv[]);
int		overflow(char *str);
int		ft_isnumstr(char *str);
int		resultcounter(long *result, int sign, char const *str, int i);
long	ft_atoi(const char *str);
void	parse_argv(t_info *info, char *argv[]);
int		data_init(t_info *info);

int		all_thread_handler(pthread_t *thread, void *(*foo)(void *)
		, void *data, t_index index);
int		all_mutex_handler(pthread_mutex_t *mutex, t_index index);
size_t	ft_strlen(const char *str);
int		ft_isdigit(int c);

void	mutex_set_bool(pthread_mutex_t *mtx, bool *dest, bool value);
bool	mutex_get_bool(pthread_mutex_t *mtx, bool *value);
void	mutex_set_long(pthread_mutex_t *mtx, long *dest, long value);
long	mutex_get_long(pthread_mutex_t *mtx, long *value);
void	mutex_long_increment(pthread_mutex_t *mutex, void *data, int inc);

long	gettime(t_time time);
bool	finished_eating(t_info *info);

void	dinner_starts(t_info *info);
void	write_status(t_philo_status status, t_info *info, t_philo *philo);
void	wait_all_threads(t_info *info);
void	*monitor_dinner(void *data);
bool	philo_died(t_philo *philo);

# endif
