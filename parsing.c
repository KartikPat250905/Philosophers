# include "philo.h"

void	parse_argv(t_info *info, char *argv[])
{
	info -> no_of_philos = ft_atoi(argv[1]);
	info -> time_to_die = ft_atoi(argv[2]);
	info -> time_to_eat = ft_atoi(argv[3]);
	info -> time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		info -> no_of_meals = ft_atoi(argv[5]);
	else
		info -> no_of_meals = -1;
}

int	philo(t_info *info)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < info->no_of_philos)
	{
		philo = info -> philos + i;
		philo -> id = i;
		philo -> no_of_meals_taken = 0;
		philo -> full = false;
		philo -> info = info;
		philo -> r_fork = &info -> forks[i];
		philo -> l_fork = &info -> forks[i%info->no_of_philos];
	}
	return (0);
}

int	data_init(t_info *info)
{
	int	i;
	int	exit;

	info -> stop_program = false;
	info->philos = malloc(sizeof(t_philo) * info->no_of_philos);
	if (info -> philos == NULL)
		return (1);
	info -> forks = malloc(sizeof(t_fork) * info->no_of_philos);
	i = 0;
	while (i < info -> no_of_philos)
	{
		exit = all_mutex_handler(&info->forks[i].fork, INIT);
		info -> forks[i].fork_id = i;
		if (exit != 0)
			return (1);
		i++;
	}
	if (philo_init(info) != 0)
		return (1);
	return (0);
}
