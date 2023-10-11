/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:18:59 by yachen            #+#    #+#             */
/*   Updated: 2023/10/11 13:37:13 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

/* Turn on dead_flag if the philo is timeout */
static int	philo_timeout(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if ((get_current_time() - philo->last_meal) > philo->time_to_die)
	{
		print_msg(philo, 'd');
		pthread_mutex_lock(philo->dead_lock);
		*(philo->dead) = 1;
		pthread_mutex_unlock(philo->dead_lock);
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

/* Check if any philo is timeout */
static int	check_any_timeout(t_philo *philo)
{
	int	i;
	int	nb_of_philos;

	i = 0;
	nb_of_philos = philo[0].nb_of_philos;
	while (i < nb_of_philos)
	{
		if (philo_timeout(philo + i) == 1)
			return (1);
		i++;
	}
	return (0);
}

/* Check if the philo eat enough times */
static int	philo_eat_enough(t_philo *philo)
{

	pthread_mutex_lock(philo->meal_lock);
	if (philo->nb_times_to_eat != 0
		&& philo->meals_eaten >= philo->nb_times_to_eat) 
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

/* Check if all philo eat enough times */
static int	check_all_eatenough(t_philo *philo)
{
	int	i;
	int	nb_of_philos;
	int	nb_philo_finisheat;

	i = 0;
	nb_of_philos = philo[0].nb_of_philos;
	nb_philo_finisheat = 0;
	while (i < nb_of_philos)
	{
		nb_philo_finisheat += philo_eat_enough(philo + i);
		i++;
	}
	if (nb_philo_finisheat == nb_of_philos)
	{
		print_msg(philo, 'F');
		pthread_mutex_lock(philo[0].dead_lock);
		*(philo[0].dead) = 1;
		pthread_mutex_unlock(philo[0].dead_lock);
		return (1);
	}
	return (0);
}

/* Monitor keep running until a philo is dead */
void	run_monitor(t_pgm *pgm)
{
	while (1)
	{
		if ((check_any_timeout(pgm->philos) == 1)
			|| (check_all_eatenough(pgm->philos) == 1))
			return ;
		usleep(200);
	}
}
