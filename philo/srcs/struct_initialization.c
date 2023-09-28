/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 14:15:56 by yachen            #+#    #+#             */
/*   Updated: 2023/09/28 17:29:11 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// initialize fork array
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

// initialize the monitor
static int	init_monitor(t_pgm *monitor)
{
	monitor->dead_flag = 0;
	if (pthread_mutex_init(&monitor->dead_lock, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&monitor->meal_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&monitor->dead_lock);
		return (-1);
	}
	if (pthread_mutex_init(&monitor->write_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&monitor->dead_lock);
		pthread_mutex_destroy(&monitor->meal_lock);
		return (-1);
	}
	monitor->philos = NULL;
	monitor->forks = NULL;
	return (0);
}

static void	init_philo2(char **av, t_philo *philo, t_pgm *mnt)
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
	philo->num_of_philos = philo_ft_atoi(av[1]);
	philo->num_times_to_eat = 0;
	if (av[5] != NULL && philo_ft_atoi(av[5]) != 0)
		philo->num_times_to_eat = philo_ft_atoi(av[5]);
	philo->dead = &mnt->dead_flag;
	philo->r_fork = NULL;
	philo->l_fork = NULL;
	philo->write_lock = &mnt->write_lock;
	philo->dead_lock = &mnt->dead_lock;
	philo->meal_lock = &mnt->meal_lock;
}

static int	init_philo1(char **av, t_philo **philo, t_pgm *mnt, pthread_mutex_t **fork)
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
		init_philo2(av, (*philo) + i, mnt);
		(*philo)[i].id = i + 1;
		(*philo)[i].r_fork = &(*fork)[i];
		if (i == nb_philo - 1)
			(*philo)[i].l_fork = &(*fork)[0];
		else
			(*philo)[i].l_fork = &(*fork)[i + 1];
		i++;
	}
	return (0);
}

int	init_all(char **av, pthread_mutex_t **fork, t_philo **philo, t_pgm *mnt)
{
	int	nb_philo;

	nb_philo = philo_ft_atoi(av[1]);
	if (init_fork(nb_philo, fork) == -1)
		return (-1);
	if (init_monitor(mnt) == -1)
	{
		clean_forks(fork, nb_philo);
		return (-1);
	}
	if (init_philo1(av, philo, mnt, fork) == -1)
	{
		clean_forks(fork, nb_philo);
		clean_monitor(mnt);
		return (-1);
	}
	mnt->philos = *philo;
	mnt->forks = *fork;
	return (0);
}

/* test if initialization is successful

void print_philo(t_philo *philo) {
    printf("t_philo structure:\n");
    printf("  id: %d\n", philo->id);
    printf("  eating: %d\n", philo->eating);
    printf("  meals_eaten: %d\n", philo->meals_eaten);
    printf("  last_meal: %zu\n", philo->last_meal);
    printf("  time_to_die: %zu\n", philo->time_to_die);
    printf("  time_to_eat: %zu\n", philo->time_to_eat);
    printf("  time_to_sleep: %zu\n", philo->time_to_sleep);
    printf("  start_time: %zu\n", philo->start_time);
    printf("  num_of_philos: %d\n", philo->num_of_philos);
    printf("  num_times_to_eat: %d\n", philo->num_times_to_eat);
    printf("  dead: %p\n", (void *)philo->dead);
    printf("  r_fork: %p\n", (void *)philo->r_fork);
    printf("  l_fork: %p\n", (void *)philo->l_fork);
    printf("  write_lock: %p\n", (void *)philo->write_lock);
    printf("  dead_lock: %p\n", (void *)philo->dead_lock);
    printf("  meal_lock: %p\n", (void *)philo->meal_lock);
}

void print_program(t_pgm *program) {
    printf("t_program structure:\n");
    printf("  dead_flag: %d\n", program->dead_flag);
	printf("  dead_flag adress: %p\n", &program->dead_flag);
    printf("  philos: %p\n", (void *)program->philos);
}

int	main(int argc, char **argv)
{
	t_pgm			monitor;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	
	init_all(argv, &forks, &philo, &monitor);
	print_program(&monitor);
	printf("\n------------");
	print_philo(&philo[0]);
	printf("\n------------");
	print_philo(&philo[1]);
	printf("\n------------");
	print_philo(&philo[2]);
	return (0);
}*/

