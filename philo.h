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
# include "libft/libft.h"
# include <stdio.h>
# include <pthread.h>

# define PHILO_MAX 300

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					times_eaten;
	int					last_meal;
	int					*dead_flag;
	int					no_of_philos;
	int					time_to_die;
	int					eating;
	int					time_to_eat;
	int					time_to_sleep;
	int					no_of_times_to_eat;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*deadlock;
	pthread_mutex_t		*meal_lock;
}				t_philo;

typedef struct s_overseer
{
	pthread_t			*philos;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	int					deathflag;
}				t_overseer;

int		checkargs(char *argv[]);
void	philo_init(t_overseer *overseer, t_philo *philo,pthread_mutex_t *forks, char *argv[]);
void	overseer_init(t_overseer *overseer, t_philo *philos);
void	forks_init(pthread_mutex_t *forks, int no_of_philos);

#endif
