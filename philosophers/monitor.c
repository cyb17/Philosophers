/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:18:59 by yachen            #+#    #+#             */
/*   Updated: 2023/10/07 17:19:07 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

static int	philo_timeout(t_philo *philo)
{
	size_t	time;

	time = get_current_time();
	pthread_mutex_lock(philo->meal_lock);
	if ((time - philo->last_meal) > philo->time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

static int	philo_eat_enough(t_philo *philo)
{

	pthread_mutex_lock(philo->meal_lock);
	if (philo->meals_eaten == philo->nb_times_to_eat)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
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
		return (1);
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
			return (1);
		i++;
	}
	return (0);
}

int	monitor(t_pgm *pgm)
{
	if ((check_all_eatenough(pgm->philos) == 1)
		|| (check_any_timeout(pgm->philos) == 1))
	{
		pthread_mutex_lock(&pgm->dead_lock);
		pgm->dead_flag = 1;
		pthread_mutex_unlock(&pgm->dead_lock);
		return (1);
	}
	return (0);
}
