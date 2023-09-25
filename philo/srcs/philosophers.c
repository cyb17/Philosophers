/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:31:45 by yachen            #+#    #+#             */
/*   Updated: 2023/09/25 18:14:08 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_fork(int nb_philo, pthread_mutex_t **fork)
{
	int	i;
	int	err;

	*fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!(*philo))
		return (-1);
	i = 0;
	err = 0;
	while (i < nb_philo)
	{
		err = pthread_mutex_init((*philo)[i]);
		if (err != 0 && i != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy((*philo)[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	init_monitor(t_program *monitor)
{
	monitor.dead_flag = 0;
	if (pthread_mutex_init(monitor.dead_lock) != 0)
		return (-1);
	if (pthread_mutex_init(monitor.meal_lock) != 0)
	{
		pthread_mutex_destroy(monitor.dead_lock);
		return (-1);
	}
	if (pthread_mutex_init(monitor.write_lock) != 0)
	{
		pthread_mutex_destroy(monitor.dead_lock);
		pthread_mutex_destroy(monitor.meal_lock);
		return (-1);
	}
	monitor.philo = NULL;
	return (0);
}

int	init_philo(int nb_philo, char **av, t_philo **philo)
{
	int	i;
	int	err;
	
	*philo = (t_philo *)malloc(sizeof(t_philo) * nb_philo);
	if (!(*philo))
		return (-1);
	i = 0;
	err = 0;
	while (i < nb_philo)
	{
		(*philo)[i].thread = 0;
		(*philo)[i].id = i + 1;
		(*philo)[i].eating = 0;
		(*philo)[i].meals_eaten = 0;
		(*philo)[i].last_meal = 0;
		(*philo)[i].time_to_die = philo_ft_atoi(av[2]);
		(*philo)[i].time_to_eat = philo_ft_atoi(av[3]);
		(*philo)[i].time_to_sleep = philo_ft_atoi(av[4]);
		(*philo)[i].start_time = 0;
		(*philo)[i].num_of_philos = nb_philo;
		(*philo)[i].num_times_to_eat = 0;
		if (av[5] != NULL)
			(*philo)[i].num_times_to_eat = philo_ft_atoi(av[5]);
		(*philo)[i].dead = NULL;
		(*philo)[i].r_fork = NULL;
		(*philo)[i].l_fork = NULL;
		(*philo)[i].write_lock = NULL;
		(*philo)[i].dead_lock = NULL;
		(*philo)[i].meal_lock = NULL;
	}
}

int	init_all(char **av, pthread_mutex_t **fork, t_philo **philo, t_progm *mnt)
{
	int	nb_philo;

	nb_philo = philo_ft_atoi(av[1]);
	if (init_fork(nb_philo, fork) == -1)
		return (-1);
	init_monitor(mnt);
	init_philo(nb_philo, argv, philo);
	
}

int	main(int argc, char **argv)
{
	t_progm		monitor;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	
	if (arguments_parsing(argc, argv) == -1
	 || init_all(argv, &forks, &philo, &monitor) == -1)
	 return (-1);
	/*philo = (t_philo *)malloc(sizeof(t_philo) * (philo_ft_atoi(argv[1])));
	forks = malloc(sizeof(pthread_mutex_t) * (philo_ft_atoi(argv[1])));
	if (!philo || !forks)
	{
		if (philo)
			free(philo);
		return (1);
	}*/
	
	return (0);
}