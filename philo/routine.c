/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:19:57 by yachen            #+#    #+#             */
/*   Updated: 2023/10/17 15:41:16 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/* Return 1 if a philo is dead to stop the thread */
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

/* Stop the philo'saction and return 1 if a philo is dead,
to stop the thread */
static int	action_time(t_philo *philo, size_t act_time)
{
	size_t	time3;

	time3 = get_current_time();
	while (get_current_time() - time3 < act_time)
	{
		if (check_dead_flag(philo) == 1)
			return (1);
		ft_usleep(1);
	}
	return (0);
}

static int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg(philo, 'f');
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, 'f');
	print_msg(philo, 'e');
	philo->eating = 1;
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	if (action_time(philo, philo->time_to_eat) == 1)
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	return (0);
}

static int	ft_sleep(t_philo *philo)
{
	print_msg(philo, 's');
	if (action_time(philo, philo->time_to_sleep) == 1)
		return (1);
	return (0);
}

static void	ft_think(t_philo *philo)
{
	size_t	thk;

	thk = 0;
	print_msg(philo, 't');
	if (philo->time_to_die > philo->time_to_sleep + philo->time_to_eat)
	{
		thk = philo->time_to_die - (philo->time_to_eat + philo->time_to_sleep);
		ft_usleep(thk - 2);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (check_dead_flag(philo) == 0)
	{
		if (philo->nb_of_philos == 1 && philo->id == 1)
		{
			pthread_mutex_lock(philo->r_fork);
			print_msg(philo, 'f');
			pthread_mutex_unlock(philo->r_fork);
			return (NULL);
		}
		if (ft_eat(philo) == 1)
			return (NULL);
		if (ft_sleep(philo) == 1)
			return (NULL);
		ft_think(philo);
	}
	return (NULL);
}
