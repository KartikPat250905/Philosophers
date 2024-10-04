#include "philo.h"

void	*single_philo(void *data)
{
	t_philo	*philo;
	t_info	*info;

	philo = data;
	info = philo -> info;
	wait_all_threads(philo -> info);
	mutex_set_long(&philo -> philo_mutex, &info -> start_time, gettime(MILLISECONDS));
	mutex_long_increment(&philo -> info -> info_mutex, &philo -> info -> running_no_of_threads, 1);
	write_status(TAKE_FIRST_FORK, info, philo);
	while (!finished_eating(philo -> info))
		usleep(200);
	return (NULL);
}

long	gettime(t_time time)
{
	struct timeval tv;

	if (gettimeofday(&tv, NULL))
	{
		printf("gettimeofday failed!!!");
		return (-1);
	}
	if (time == MILLISECONDS)
		return ((tv.tv_sec * 1000 + (tv.tv_usec / 1000)));
	else if (time == MICROSECONDS)
		return ((tv.tv_sec * 1000000) + tv.tv_usec);
	else
	{
		printf("Error with the give time code to gettime");
		return (-1);
	}
}

void	mutex_long_increment(pthread_mutex_t *mutex, void *data, int inc)
{
	long	*value;

	value = data;
	all_mutex_handler(mutex, LOCK);
	*value = *value + inc;
	all_mutex_handler(mutex, UNLOCK);
}

void	write_status(t_philo_status status, t_info *info, t_philo *philo)
{
	long	elapsed;

	elapsed = gettime(MILLISECONDS) - info -> start_time;
	if (finished_eating(info))
		return ;
	all_mutex_handler(&info->write_lock, LOCK);
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& (!(finished_eating(info))))
		printf("%ld %d has taken a fork\n",elapsed, philo -> id);
	else if (status == SLEEPING && (!(finished_eating(info))))
		printf("%ld %d is sleeping\n",elapsed, philo -> id);
	else if (status == THINKING && (!(finished_eating(info))))
		printf("%ld %d is thinking\n",elapsed, philo -> id);
	else if (status == DIED && (!(finished_eating(info))))
		printf("%ld %d died\n",elapsed, philo -> id);
	else if (status == EATING && (!(finished_eating(info))))
		printf("%ld %d is eating\n",elapsed, philo -> id);
	else
		printf("Please enter a valid philo status for the write status function.\n");
	all_mutex_handler(&info->write_lock, UNLOCK);
}

bool	finished_eating(t_info *info)
{
	return (mutex_get_bool(&info->info_mutex, &info->stop_program));
}