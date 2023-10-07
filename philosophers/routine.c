#include "./includes/philosophers.h"

int	check_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	action_time(t_philo *philo, size_t act_time)
{
	size_t	time1;
	size_t	time2;
	size_t	time3;

	time3 = get_current_time();
	while (get_current_time() - time3 < act_time)
	{
		time1 = get_current_time();
		if (check_dead_flag(philo) == 1)
			break ;
		time2 = get_current_time();
		ft_usleep(10 - (time2 - time1));
	}

}

void	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	print_msg(philo, 'e');
	philo->eating = 1;
	philo->last_meal = get_current_time();
	action_time(philo, philo->time_to_eat);
	philo->meals_eaten++;
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
}

void	sleep(t_philo *philo)
{
	print_msg(philo, 's');
	action_time(philo, philo->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_msg(philo,'t');
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_dead_flag(philo) == 0)
	{
		eat(philo);
		sleep(philo);
		think(philo);
	}
}
