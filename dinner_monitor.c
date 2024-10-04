# include "philo.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	t_info	*info;

	info = philo -> info;
	elapsed = gettime(MILLISECONDS) - mutex_get_long(&philo -> philo_mutex, &philo -> last_meal_time);
	if (mutex_get_bool(&philo -> philo_mutex, &philo -> full))
		return (false);
	if (elapsed > mutex_get_long(&info -> info_mutex, &info -> time_to_die))
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_info *info;

	info = (t_info *)data;
	while (mutex_get_long(&info -> info_mutex, &info -> running_no_of_threads) != info -> no_of_philos)
		usleep(500);
	while (!finished_eating(info))
	{
		i = 0;
		while(i < info->no_of_philos)
		{
			if (philo_died(&info->philos[i]))
			{
				write_status(DIED, info, &info -> philos[i]);
				mutex_set_bool(&info->info_mutex, &info->stop_program, true);
			}
			i++;
		}
	}
	return (NULL);
}