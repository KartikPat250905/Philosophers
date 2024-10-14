/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:44:57 by karpatel          #+#    #+#             */
/*   Updated: 2024/10/12 14:44:58 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think(t_philo *philo, bool start)
{
	long	t_think;

	if (!start)
		write_status(THINKING, philo -> info, philo);
	if (philo -> info -> no_of_philos % 2 == 0)
		return ;
	t_think = (philo -> info -> time_to_eat * 2)
		- philo -> info -> time_to_sleep;
	if (t_think < 0)
		t_think = 0;
	ft_usleep(t_think * 0.42, philo);
}

void	eat(t_philo *philo)
{
	all_mutex_handler(&philo -> first_fork -> fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo -> info, philo);
	all_mutex_handler(&philo -> second_fork -> fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo -> info, philo);
	mutex_set_long(&philo -> philo_mutex,
		&philo->last_meal_time, gettime(MILLISECONDS));
	write_status(EATING, philo->info, philo);
	ft_usleep(philo -> info -> time_to_eat, philo);
	if ((philo->info->no_of_meals > 0)
		&& (philo->no_of_meals_taken == philo->info->no_of_meals))
		mutex_set_bool(&philo -> philo_mutex, &philo -> full, true);
	all_mutex_handler(&philo-> first_fork -> fork, UNLOCK);
	all_mutex_handler(&philo->second_fork -> fork, UNLOCK);
}

void	contention_preventer(t_philo *philo)
{
	if (philo -> info -> no_of_philos % 2 == 0)
	{
		if ((philo -> id + 1) % 2 == 0)
			ft_usleep(30, philo);
	}
	else
	{
		if (philo -> id % 2 != 0)
			think(philo, true);
	}
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	mutex_long_increment(&philo -> info -> info_mutex,
		&philo -> info -> running_no_of_threads, 1);
	wait_all_threads(philo->info);
	contention_preventer(philo);
	while (!finished_eating(philo->info))
	{
		eat(philo);
		write_status(SLEEPING, philo -> info, philo);
		ft_usleep(philo -> info -> time_to_sleep, philo);
		mutex_long_increment(&philo -> philo_mutex,
			&philo -> no_of_meals_taken, 1);
		if (mutex_get_long(&philo->philo_mutex,
				&philo->no_of_meals_taken) == philo -> info -> no_of_meals)
			mutex_set_bool(&philo -> philo_mutex, &philo -> full, true);
		think(philo, false);
	}
	return (NULL);
}

void	dinner_starts(t_info *info)
{
	int	i;

	i = 0;
	info -> start_time = gettime(MILLISECONDS);
	philo_last_meal_time(info);
	if (info->no_of_meals == 0)
		return ;
	else if (info -> no_of_philos == 1)
	{
		all_thread_handler(&info->philos[i].thread_id,
			single_philo, &info->philos[i], CREATE);
	}
	else
	{
		all_thread_handler(&info -> monitor, monitor_dinner, info, CREATE);
		while (i < info->no_of_philos)
		{
			all_thread_handler(&info->philos[i].thread_id,
				dinner_simulation, &info->philos[i], CREATE);
			i++;
		}
	}
	mutex_set_bool(&info->info_mutex, &info->all_threads_ready, true);
	join_threads(info);
}
