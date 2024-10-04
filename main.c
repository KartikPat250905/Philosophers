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

//200 800 200 200
//5 600 150 150
int	main(int argc, char *argv[])
{
	t_info	info;

	if ((argc != 5 && argc != 6) || !checkargs(argv))
	{
		printf("Incorrect usuage check the instructons to run correctly.\n");
		return (EXIT_FAILURE);
	}
	parse_argv(&info, argv);
	if (data_init(&info) != 0)
	{
		printf("Error with mallocing stuff for mutexs or threads in info struct.");
		return (EXIT_FAILURE);
	}
	dinner_starts(&info);
	//cleaner(info.phi);
}
