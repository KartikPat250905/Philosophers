/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_monitor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:36:30 by karpatel          #+#    #+#             */
/*   Updated: 2024/10/12 14:36:35 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	t_info	*info;

	info = philo -> info;
	elapsed = gettime(MILLISECONDS)-mutex_get_long(&philo -> philo_mutex,
			&philo -> last_meal_time);
	if (mutex_get_bool(&philo -> philo_mutex, &philo -> full))
		return (false);
	if (elapsed > mutex_get_long(&info -> info_mutex, &info -> time_to_die))
		return (true);
	return (false);
}

void	all_philos_full(t_info *info)
{
	int		no_of_philos_full;
	t_philo	*philo;
	int		i;

	no_of_philos_full = 0;
	if (info -> no_of_meals == -1)
		return ;
	i = 0;
	while (i < info -> no_of_philos)
	{
		philo = &info -> philos[i];
		if (mutex_get_bool(&philo->philo_mutex, &philo -> full))
			no_of_philos_full++;
		i++;
	}
	if (no_of_philos_full == info -> no_of_philos)
	{
		all_mutex_handler(&info -> write_lock, LOCK);
		printf("The philosophers have eaten the required amount of meals.\n");
		mutex_set_bool(&info -> info_mutex, &info -> stop_program, true);
		all_mutex_handler(&info -> write_lock, UNLOCK);
	}
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_info	*info;

	info = (t_info *)data;
	while (mutex_get_long(&info -> info_mutex,
			&info -> running_no_of_threads) != info -> no_of_philos)
		usleep(500);
	while (!finished_eating(info))
	{
		i = 0;
		while (i < info->no_of_philos)
		{
			if (philo_died(&info->philos[i]))
			{
				write_status(DIED, info, &info -> philos[i]);
				mutex_set_bool(&info->info_mutex, &info->stop_program, true);
				i = info -> no_of_philos;
			}
			i++;
		}
		all_philos_full(info);
	}
	return (NULL);
}
