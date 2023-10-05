/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:31:45 by yachen            #+#    #+#             */
/*   Updated: 2023/10/02 16:10:13 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	even_take_forks(t_philo *philo)
{
	if (unlock_mutex(philo, '\0') == 1)
		return ;
	pthread_mutex_lock(philo->r_fork);
	if (unlock_mutex(philo, 'r') == 1)
		return ;
	print_msg(philo, 'f');
	pthread_mutex_lock(philo->l_fork);
	if (unlock_mutex(philo, 'b') == 1)
		return ;
	print_msg(philo, 'f');
	if (unlock_mutex(philo, 'b') == 1)
		return ;
	print_msg(philo, 'e');
	philo->last_meal = get_current_time();
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_lock(philo->meal_lock);
	if (philo->meals_eaten == philo->num_times_to_eat)
		(*philo->meal)++;
	pthread_mutex_unlock(philo->meal_lock);
	if (unlock_mutex(philo, 'b') == 1)
		return ;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	odd_take_forks(t_philo *philo)
{
	if (unlock_mutex(philo, '\0') == 1)
		return ;
	pthread_mutex_lock(philo->l_fork);
	if ((unlock_mutex(philo, 'l') == 1) || (case_1_philo(philo) == 1))
		return ;
	print_msg(philo, 'f');
	pthread_mutex_lock(philo->r_fork);
	if (unlock_mutex(philo, 'b') == 1)
		return ;
	print_msg(philo, 'f');
	if (unlock_mutex(philo, 'b') == 1)
		return ;
	print_msg(philo, 'e');
	philo->last_meal = get_current_time();
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten++;
	pthread_mutex_lock(philo->meal_lock);
	if (philo->meals_eaten == philo->num_times_to_eat)
		(*philo->meal)++;
	pthread_mutex_unlock(philo->meal_lock);
	if (unlock_mutex(philo, 'b') == 1)
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
		if (philo->id % 2 != 0)
			odd_take_forks(philo);
		else
			even_take_forks(philo);
		if (unlock_mutex(philo, '\0') == 1)
			return (NULL);
		print_msg(philo, 's');
		ft_usleep(philo->time_to_sleep);
		if (unlock_mutex(philo, '\0') == 1)
			return (NULL);
		print_msg(philo, 't');
		if (unlock_mutex(philo, '\0') == 1)
			return (NULL);
		if (check_philo_death(philo) == 1)
			return (NULL);
	}
	return (NULL);
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
	while (i < philo[0].num_of_philos)
	{
		if (pthread_create(&philo[i].thread, NULL, &routine, &philo[i]) != 0)
		{
			printf("Error : pthread_create\n");
			break ;
		}
		i++;
	}
	j = 0;
	while (j < i)
		pthread_join(philo[j++].thread, NULL);
	clean_all(&pgm);
	return (0);
}
