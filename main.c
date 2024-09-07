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

int	main(int argc, char *argv[])
{
	t_info	info;

	if (!((argc == 5 && checkargs(argv)) || (argc == 6 && checkargs(argv))))
	{
		printf("Incorrect usuage check the instructons to run correctly.\n");
		return (EXIT_FAILURE);
	}
	parse_argv(&info, argv);
	if (data_init(&info) != 0)
	{
		printf("Error with mallocing stuff or mutexs or threads.");
		return (EXIT_FAILURE);
	}
	//dinner_starts();
	//clean();
}
