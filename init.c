/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:36:55 by karpatel          #+#    #+#             */
/*   Updated: 2024/08/24 16:36:56 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philo.h"

int	checkargs(char *argv[])
{
	int	i;

	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[2]) == 0 || ft_atoi(argv[4]) == 0)
		return (0);
	i = 2;
	while (argv[i])
	{
		if (ft_isnumstr(argv[i]))
			return (0);
		if (overflow(argv[i]))
			return (0);
		if(*argv[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

void	overseer_init(t_overseer *overseer, t_philo *philos)
{
	overseer -> philos = philos;
	overseer -> deathflag = 0;
	pthread_mutex_init(&overseer -> dead_lock, NULL);
	pthread_mutex_init(&overseer -> meal_lock, NULL);
	pthread_mutex_init(&overseer -> write_lock, NULL);
}

void	forks_init(pthread_mutex_t *forks, int no_of_philos)
{
	int	i;

	i = 0;
	while (i < no_of_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	philo_init(t_overseer *overseer, t_philo *philo,
	pthread_mutex_t *forks, char *argv[])
{
	int	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].times_eaten = 0;
		philo[i].eating = 0;
		philo[i].no_of_philos = argv[1];
		philo[i].time_to_die = argv[2];
		philo[i].time_to_eat = argv[3];
		philo[i].time_to_sleep = argv[4];
		if (argv[5])
			philo[i].no_of_times_to_eat = ft_atoi(argv[5]);
		else
			philo[i].no_of_times_to_eat = -1;
		philo[i].l_fork = &forks[i];
		if (i == 0)
			philo[i].r_fork = &forks[ft_atoi(argv[1]) - 1];
		else
			philo[i].r_fork = &forks[i - 1];
		i++;
	}
}
