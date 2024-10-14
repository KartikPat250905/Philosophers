/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:29:52 by karpatel          #+#    #+#             */
/*   Updated: 2024/10/12 15:29:54 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_set_bool(pthread_mutex_t *mtx, bool *dest, bool value)
{
	all_mutex_handler(mtx, LOCK);
	*dest = value;
	all_mutex_handler(mtx, UNLOCK);
}

bool	mutex_get_bool(pthread_mutex_t *mtx, bool *value)
{
	bool	ans;

	all_mutex_handler(mtx, LOCK);
	ans = *value;
	all_mutex_handler(mtx, UNLOCK);
	return (ans);
}

void	mutex_set_long(pthread_mutex_t *mtx, long *dest, long value)
{
	all_mutex_handler(mtx, LOCK);
	*dest = value;
	all_mutex_handler(mtx, UNLOCK);
}

long	mutex_get_long(pthread_mutex_t *mtx, long *value)
{
	long	ans;

	all_mutex_handler(mtx, LOCK);
	ans = *value;
	all_mutex_handler(mtx, UNLOCK);
	return (ans);
}
