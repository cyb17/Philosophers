/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:15:56 by yachen            #+#    #+#             */
/*   Updated: 2023/10/09 16:01:13 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

static int	init_fork(int nb_philo, pthread_mutex_t **fork)
{
	int	i;
	int	err;

	*fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!(*fork))
		return (-1);
	i = 0;
	err = 0;
	while (i < nb_philo)
	{
		err = pthread_mutex_init(&(*fork)[i], NULL);
		if (err != 0 && i != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&(*fork)[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

static int	init_pgm(t_pgm *pgm, int nb_philo)
{
	pgm->dead_flag = 0;
	if (pthread_mutex_init(&pgm->write_lock, NULL) != 0)
		return (-1);
	if (init_fork(nb_philo, &pgm->meal_lock) == -1)
	{
		pthread_mutex_destroy(&pgm->write_lock);
		return (-1);
	}
	if (pthread_mutex_init(&pgm->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&pgm->write_lock);
		clean_forks(&pgm->meal_lock, nb_philo);
	//	pthread_mutex_destroy(&pgm->meal_lock);
		return (-1);
	}
	pgm->philos = NULL;
	pgm->forks = NULL;
	return (0);
}

static void	init_2(char **av, t_philo *philo, t_pgm *pgm)
{
	philo->thread = 0;
	philo->id = 0;
	philo->eating = 0;
	philo->meals_eaten = 0;
	philo->last_meal = get_current_time();
	philo->time_to_die = philo_ft_atoi(av[2]);
	philo->time_to_eat = philo_ft_atoi(av[3]);
	philo->time_to_sleep = philo_ft_atoi(av[4]);
	philo->start_time = get_current_time();
	philo->nb_of_philos = philo_ft_atoi(av[1]);
	philo->nb_times_to_eat = 0;
	if (av[5] != NULL && philo_ft_atoi(av[5]) != 0)
		philo->nb_times_to_eat = philo_ft_atoi(av[5]);
	philo->dead = &pgm->dead_flag;
	philo->r_fork = NULL;
	philo->l_fork = NULL;
	philo->write_lock = &pgm->write_lock;
	philo->meal_lock = pgm->meal_lock;
	philo->dead_lock = &pgm->dead_lock;
}

int	init_1(char **av, t_philo **philo, t_pgm *pgm, pthread_mutex_t **fork)
{
	int	i;
	int	err;
	int	nb_philo;

	i = 0;
	err = 0;
	nb_philo = philo_ft_atoi(av[1]);
	*philo = (t_philo *)malloc(sizeof(t_philo) * nb_philo);
	if (!(*philo))
		return (-1);
	while (i < nb_philo)
	{
		init_2(av, (*philo) + i, pgm);
		(*philo)[i].id = i + 1;
		if ((*philo)[i].id % 2 == 0)
		{
			(*philo)[i].r_fork = &(*fork)[i];
			if (i == nb_philo - 1)
				(*philo)[i].l_fork = &(*fork)[0];
			else
				(*philo)[i].l_fork = &(*fork)[i + 1];
		}
		else
		{
			(*philo)[i].r_fork = &(*fork)[i + 1];
			if (i == nb_philo - 1)
			{
				(*philo)[i].r_fork = &(*fork)[i];
				(*philo)[i].l_fork = &(*fork)[0];
			}
			else
				(*philo)[i].l_fork = &(*fork)[i];
		}
		i++;
	}
	return (0);
}

int	init_all(char **av, pthread_mutex_t **fork, t_philo **ph, t_pgm *pgm)
{
	int	nb_philo;

	nb_philo = philo_ft_atoi(av[1]);
	if (init_fork(nb_philo, fork) == -1)
		return (-1);
	if (init_pgm(pgm, nb_philo) == -1)
	{
		clean_forks(fork, nb_philo);
		return (-1);
	}
	if (init_1(av, ph, pgm, fork) == -1)
	{
		clean_forks(fork, nb_philo);
		clean_forks(&pgm->meal_lock, nb_philo);
		pthread_mutex_destroy(&pgm->write_lock);
	//	pthread_mutex_destroy(&pgm->meal_lock);
		pthread_mutex_destroy(&pgm->dead_lock);
		return (-1);
	}
	pgm->philos = *ph;
	pgm->forks = *fork;
	return (0);
}
