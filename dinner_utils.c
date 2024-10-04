# include "philo.h"

void	wait_all_threads(t_info *info)
{
	bool	state;

	state = false;
	while (!state)
	{
		state = mutex_get_bool(&info->info_mutex, &info->all_threads_ready);
	}
}