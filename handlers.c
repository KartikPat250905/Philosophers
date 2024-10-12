/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:27:01 by karpatel          #+#    #+#             */
/*   Updated: 2024/10/12 15:27:02 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_mutex_handler(pthread_mutex_t *mutex, t_index index)
{
	int	status;

	status = 0;
	if (index == LOCK)
		status = pthread_mutex_lock(mutex);
	else if (index == UNLOCK)
		status = pthread_mutex_unlock(mutex);
	else if (index == INIT)
		status = pthread_mutex_init(mutex, NULL);
	else if (index == DESTROY)
		status = pthread_mutex_destroy(mutex);
	return (status);
}

int	all_thread_handler(pthread_t *thread, void *(*foo)(void *)
		, void *data, t_index index)
{
	int	status;

	status = 0;
	if (index == CREATE)
		status = pthread_create(thread, NULL, foo, data);
	else if (index == JOIN)
		status = pthread_join(*thread, NULL);
	else if (index == DETACH)
		status = pthread_detach(*thread);
	return (status);
}
