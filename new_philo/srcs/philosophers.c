/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:31:45 by yachen            #+#    #+#             */
/*   Updated: 2023/10/05 17:04:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	eating(t_philo *philo)
{
	print_msg(philo, 'e');
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
}

static void	even_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	if (philo_is_dead(philo, 'r') == 1)
		return ;
	print_msg(philo, 'f');
	pthread_mutex_lock(philo->l_fork);
	if (philo_is_dead(philo, 'b') == 1)
		return ;
	print_msg(philo, 'f');
	eating(philo);
	if (philo_is_dead(philo, 'b') == 1)
		return ;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	odd_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	if (philo_is_dead(philo, 'l') == 1)
		return ;
	print_msg(philo, 'f');
	pthread_mutex_lock(philo->r_fork);
	if (philo_is_dead(philo, 'b') == 1)
		return ;
	print_msg(philo, 'f');
	eating(philo);
	if (philo_is_dead(philo, 'b') == 1)
		return ;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo_is_dead(philo, '0') == 1)
			return (NULL);
		if (philo->id % 2 != 0)
			odd_take_forks(philo);
		else
			even_take_forks(philo);
		if (philo_is_dead(philo, '0') == 1)
			return (NULL);
		print_msg(philo, 's');
		ft_usleep(philo->time_to_sleep);
		if (philo_is_dead(philo, '0') == 1)
			return (NULL);
		print_msg(philo, 't');
		if (philo->meals_eaten == philo->nb_times_to_eat)
			return (NULL);
	}
	return (NULL);
}

int	philo_timeout(t_pgm *pgm, int i)
{
	if (get_current_time() - pgm->philos[i].start_time > pgm->philos[i].time_to_die
		&& get_current_time() - pgm->philos[i].last_meal > pgm->philos[i].time_to_die
		&& pgm->philos[i].eating == 0)
	{
		pthread_mutex_lock(&pgm->dead_lock);
		pgm->dead_flag = 1;
		pthread_mutex_unlock(&pgm->dead_lock);
		print_msg(pgm->philos + i, 'd');
		return (1);
	}
	return (0);
}

int	philo_eatenough(t_pgm *pgm, int i, int *nb_philos_eatenough)
{
	if (pgm->philos[i].meals_eaten == pgm->philos[i].nb_times_to_eat
		&& pgm->philos[i].nb_times_to_eat != 0)
	{
		(*nb_philos_eatenough)++;
		if (*nb_philos_eatenough == pgm->philos[i].nb_of_philos)
		{
			pthread_mutex_lock(&pgm->dead_lock);
			pgm->dead_flag = 1;
			pthread_mutex_unlock(&pgm->dead_lock);
			print_msg(pgm->philos + i, 'F');
			return (1);
		}
	}
	return (0);
}

int	ft_monitor(t_pgm *pgm)
{
	int	i;
	int	nb_philos_eatenough;

	i = 0;
	nb_philos_eatenough = 0;
	while (i < pgm->philos[0].nb_of_philos)
	{
		if ((philo_timeout(pgm, i) == 1)
			|| (philo_eatenough(pgm, i, &nb_philos_eatenough) == 1))
			return (1);
	}
	return (0);
}

int	create_thread(t_philo *philo, int *i)
{
	while (*i < philo[0].nb_of_philos)
	{
		if (pthread_create(&philo[*i].thread, NULL, &routine, &philo[*i]) != 0)
		{
			printf("Error : pthread_create\n");
			return (-1);
		}
		(*i)++;
	}
	return (0);
}

void	run_monitor(t_pgm *pgm)
{
	while (1)
	{
		if (ft_monitor(pgm) == 1)
			break ;
		ft_usleep(500);
	}
}

int	main(int argc, char **argv)
{
	t_pgm			pgm;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				i;
	int				j;

	i = 0;
	if (arguments_parsing(argc, argv) == -1
		|| init_all(argv, &forks, &philo, &pgm) == -1)
		return (-1);
	if (create_thread(philo, &i) == 0)
		run_monitor(&pgm);
	j = 0;
	while (j < i)
		pthread_join(philo[j++].thread, NULL);
	clean_all(&pgm);
	return (0);
}
