/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 14:40:43 by karpatel          #+#    #+#             */
/*   Updated: 2024/10/12 14:40:45 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_all_threads(t_info *info)
{
	bool	state;

	state = false;
	while (!state)
	{
		state = mutex_get_bool(&info->info_mutex, &info->all_threads_ready);
	}
}

void	ft_usleep(size_t millisecs, t_philo *philo)
{
	size_t	start;
	size_t	i;
	t_info	*info;

	start = gettime(MILLISECONDS);
	info = philo -> info;
	i = 0;
	while (gettime(MILLISECONDS) - start < millisecs)
	{
		if (i % 100 == 0)
		{
			if (philo_died(philo) && mutex_get_bool
				(&info -> info_mutex, &info->stop_program))
				return ;
		}
		i++;
		usleep(500);
	}
}

void	*single_philo(void *data)
{
	t_philo	*philo;
	t_info	*info;

	philo = data;
	info = philo -> info;
	wait_all_threads(philo -> info);
	mutex_set_long(&philo -> philo_mutex,
		&philo -> last_meal_time, gettime(MILLISECONDS));
	mutex_long_increment(&philo -> info -> info_mutex,
		&philo -> info -> running_no_of_threads, 1);
	write_status(TAKE_FIRST_FORK, info, philo);
	while (!philo_died(philo))
		ft_usleep(9, philo);
	write_status(DIED, info, philo);
	return (NULL);
}

void	join_threads(t_info *info)
{
	int	i;

	i = 0;
	while (i < info -> no_of_philos)
	{
		all_thread_handler(&info->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}
