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

