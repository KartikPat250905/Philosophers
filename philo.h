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
# include "sys/time.h"

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

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}				t_fork;

typedef struct s_info
{
	long	no_of_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	no_of_meals;
	long	start_time;
	bool	stop_program;
	t_fork	*forks;
	t_philo	*philos;
}				t_info;

typedef struct s_philo
{
	int			id;
	int			no_of_meals_taken;
	bool		full;
	long		last_meal_time;
	t_fork		*l_fork;
	t_fork		*r_fork;
	pthread_t	thread_id;
	t_info		*info;
}				t_philo;

// Input handling functions
int		checkargs(char *argv[]);
int		overflow(char *str);
int		ft_isnumstr(char *str);
int		resultcounter(long *result, int sign, char const *str, int i);
long	ft_atoi(const char *str);
void	parse_argv(t_info *info, char *argv[]);

int		all_thread_handler(pthread_t *thread, void *(*foo)(void *)
		, void *data, t_index index);
int		all_mutex_handler(pthread_mutex_t *mutex, t_index index);

#endif
