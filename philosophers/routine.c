/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:19:57 by yachen            #+#    #+#             */
/*   Updated: 2023/10/14 14:08:32 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

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
		usleep(500);
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
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	philo->eating = 0;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
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
	print_msg(philo,'t');
	usleep(1);
/*	if (philo->id % 2 != 0 && philo->id != philo->nb_of_philos)
		ft_usleep(philo->time_to_eat);
	else if (philo->id % 2 == 0)
	{
		ft_usleep(philo->time_to_eat * 2);
		usleep(1);
	}
	else
	{
		ft_usleep(philo->time_to_eat * 2);
		usleep(1);
	}*/
}

/* Odd start their routine first, and then even start theirs,
 we don't need to put many times check death fonction in the action functions
because it will be done very very quickly and it's does not influence the monitor job
and displaying time.
put check death function in while condition and in action_time() is enough */
void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	/*if (philo->nb_of_philos % 2 != 0 && philo->id == philo->nb_of_philos)
	{
		ft_usleep(philo->time_to_eat * 2);
		usleep(1);
	}*/
	if (philo->id % 2 == 0)
		usleep(1);
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

