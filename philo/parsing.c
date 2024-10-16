/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:30:25 by karpatel          #+#    #+#             */
/*   Updated: 2024/10/12 15:30:26 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_argv(t_info *info, char *argv[])
{
	info -> no_of_philos = ft_atoi(argv[1]);
	info -> time_to_die = ft_atoi(argv[2]);
	info -> time_to_eat = ft_atoi(argv[3]);
	info -> time_to_sleep = ft_atoi(argv[4]);
	if (argv[5] != NULL)
		info -> no_of_meals = ft_atoi(argv[5]);
	else
		info -> no_of_meals = -1;
	if (info -> no_of_philos <= 0 || info -> time_to_die <= 0
		|| info -> time_to_eat || info -> time_to_sleep <= 0
		|| info -> no_of_meals <= 0)
		return (1);
	return (0);
}

void	philo_fork_assign(t_philo *philo, t_info *info, int i)
{
	if (philo -> id % 2 == 0)
	{
		philo -> first_fork = &info
			-> forks[(i + 1) % info -> no_of_philos];
		philo -> second_fork = &info -> forks[i];
	}
	else
	{
		philo -> first_fork = &info -> forks[i];
		philo -> second_fork = &info
			-> forks[(i + 1) % info -> no_of_philos];
	}
}

//even philo take left fork first and the odd philo takes the right one
void	philo(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < info->no_of_philos)
	{
		philo = info -> philos + i;
		philo -> id = i;
		philo -> no_of_meals_taken = 0;
		philo -> full = false;
		philo -> info = info;
		all_mutex_handler(&philo -> philo_mutex, INIT);
		philo_fork_assign(philo, info, i);
		i++;
	}
}

int	data_init(t_info *info)
{
	int	i;
	int	exit;

	info -> stop_program = false;
	info -> all_threads_ready = false;
	info -> running_no_of_threads = 0;
	all_mutex_handler(&info->info_mutex, INIT);
	all_mutex_handler(&info -> write_lock, INIT);
	info->philos = malloc(sizeof(t_philo) * info->no_of_philos);
	if (info -> philos == NULL)
		return (1);
	info -> forks = malloc(sizeof(t_fork) * info->no_of_philos);
	i = 0;
	while (i < info -> no_of_philos)
	{
		exit = all_mutex_handler(&info->forks[i].fork, INIT);
		info -> forks[i].fork_id = i;
		if (exit != 0)
			return (1);
		i++;
	}
	philo(info);
	return (0);
}
