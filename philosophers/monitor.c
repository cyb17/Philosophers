/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:18:59 by yachen            #+#    #+#             */
/*   Updated: 2023/10/09 16:55:08 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

static int	philo_timeout(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock + (philo->id - 1));
	if ((get_current_time() - philo->last_meal) > philo->time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock + (philo->id - 1));
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock + (philo->id - 1));
	return (0);
}

static int	check_any_timeout(t_philo *philo)
{
	int	i;
	int	nb_of_philos;

	i = 0;
	nb_of_philos = philo[0].nb_of_philos;
	while (i < nb_of_philos)
	{
		if (philo_timeout(philo + i) == 1)
		{
			print_msg(philo + i, 'd');
			return (1);
		}
		i++;
	}
	return (0);
}

static int	philo_eat_enough(t_philo *philo)
{

	pthread_mutex_lock(philo->meal_lock + (philo->id - 1));
	if (philo->nb_times_to_eat != 0
		&& philo->meals_eaten >= philo->nb_times_to_eat) 
	{
		pthread_mutex_unlock(philo->meal_lock + (philo->id - 1));
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock + (philo->id - 1));
	return (0);
}

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
		return (1);
	}
	return (0);
}

int	monitor(t_pgm *pgm)
{
	if ((check_any_timeout(pgm->philos) == 1)
		|| (check_all_eatenough(pgm->philos) == 1))
	{
		pthread_mutex_lock(&pgm->dead_lock);
		pgm->dead_flag = 1;
		pthread_mutex_unlock(&pgm->dead_lock);
		return (1);
	}
	return (0);
}
