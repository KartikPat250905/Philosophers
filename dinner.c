#include "philo.h"

void	think(t_philo *philo, bool start)
{
	long t_think;

	if (!start)
		write_status(THINKING, philo -> info, philo);
	if (philo -> info -> no_of_philos % 2 == 0)
		return ;
	t_think = (philo -> info -> time_to_eat * 2) - philo -> info -> time_to_sleep;
	write_status(THINKING, philo -> info, philo);
	if (t_think < 0)
		t_think = 0;
	usleep(t_think * 0.42);
}

void	eat(t_philo *philo)
{
	all_mutex_handler(&philo -> first_fork -> fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo -> info, philo);
	all_mutex_handler(&philo -> second_fork -> fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo -> info, philo);
	mutex_set_long(&philo -> philo_mutex, &philo->last_meal_time, gettime(MILLISECONDS));
	write_status(EATING, philo -> info, philo);
	usleep(philo -> info -> time_to_eat * 1000);
	if ((philo->info->no_of_meals > 0) && (philo->no_of_meals_taken == philo->info->no_of_meals))
		mutex_set_bool(&philo -> philo_mutex, &philo -> full, true);
	all_mutex_handler(&philo-> first_fork -> fork, UNLOCK);
	all_mutex_handler(&philo->second_fork -> fork, UNLOCK);
}

void	contention_preventer(t_philo *philo)
{
	if (philo -> info -> no_of_philos % 2 == 0)
	{
		if (philo -> id % 2 == 0)
			usleep(30000);
	}
	else
	{
		if (philo -> id % 2 == 0)
			think(philo, true);
	}
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	mutex_long_increment(&philo -> info -> info_mutex, &philo -> info -> running_no_of_threads, 1);
	wait_all_threads(philo->info);
	philo -> last_meal_time = gettime(MILLISECONDS);
	contention_preventer(philo);
	while (!finished_eating(philo->info))
	{
		if (philo -> full)
			break ;
		eat(philo);
		write_status(SLEEPING, philo -> info, philo);
		usleep(1000 * philo -> info -> time_to_sleep);
		mutex_long_increment(&philo -> philo_mutex, &philo -> no_of_meals_taken, 1);
		think(philo, false);
	}
	return (NULL);
}

void	dinner_starts(t_info *info)
{
	int	i;

	i = 0;
	if (info->no_of_meals == 0)
		return ;
	else
	{
		all_thread_handler(&info -> monitor, monitor_dinner, info, CREATE);
		while (i < info->no_of_philos)
		{
			all_thread_handler(&info->philos[i].thread_id,
						dinner_simulation, &info->philos[i], CREATE);
			i++;
		}
		mutex_set_long(&info -> info_mutex, &info -> start_time, gettime(MILLISECONDS));
		mutex_set_bool(&info->info_mutex, &info->all_threads_ready, true);
		i = 0;
		while (i < info -> no_of_philos)
		{
			all_thread_handler(&info->philos[i].thread_id, NULL, NULL, JOIN);
			i++;
		}
	}
}
