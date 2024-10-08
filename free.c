# include "philo.h"

void	cleaner(t_info *info)
{
	int		i;

	i = 0;
	while (i < info -> no_of_philos)
	{
		all_mutex_handler(&info->philos[i].philo_mutex, DESTROY);
		i++;
	}
	all_mutex_handler(&info -> write_lock, DESTROY);
	all_mutex_handler(&info -> info_mutex, DESTROY);
	free(info -> forks);
	free(info -> philos);
}