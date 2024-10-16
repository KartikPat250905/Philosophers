/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:24:40 by karpatel          #+#    #+#             */
/*   Updated: 2024/10/15 15:30:08 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_info	info;

	memset(&info, 0, sizeof(t_info));
	if (((argc != 5 && argc != 6) || !checkargs(argv))
		|| (argv[5] != NULL && (ft_atoi(argv[5]) == 0)))
	{
		printf("Incorrect usage, check the instructions to run correctly.\n"
			"./philo <no.of philos> <time to die> "
			"<time to sleep> <no.of meals (optional)>\n");
		return (EXIT_FAILURE);
	}
	if (parse_argv(&info, argv))
	{
		printf("Please enter valid values.");
		return (EXIT_FAILURE);
	}
	if (data_init(&info) != 0)
	{
		printf("Error with mallocing stuff.");
		return (EXIT_FAILURE);
	}
	dinner_starts(&info);
	cleaner(&info);
}
