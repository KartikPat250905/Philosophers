/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:24:40 by karpatel          #+#    #+#             */
/*   Updated: 2024/08/24 16:24:42 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//fix atoi minor issues and complete the arguments handling.

int	main(int argc, char *argv[])
{
	t_overseer		overseer;
	t_philo			philo[PHILO_MAX];
	pthread_mutex_t	forks[PHILO_MAX];

	if (!(argc == 5 && checkargs(argv) || (argc == 6 && checkargs(argv))))
	{
		perror("Incorrect usuage check the instructons to run correctly.");
		return (1);
	}
	overseer_init(&overseer, &philo);
	forks_init(forks, ft_atoi(argv[1]));
	philo_init(overseer, philo , forks, argv);
}
