/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:31:45 by yachen            #+#    #+#             */
/*   Updated: 2023/09/26 16:45:05 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_msg(t_philo *philo, char indice)
{
	pthread_mutex_lock(*(philo->write_lock));
	get_current_time();
	if (indice == 'f')
		printf("%s%d%s %shas taken a fork%s\n", WHE, philo_id, DEF, YEW, DEF);
	else if (indice == 'e')
		printf("%s%d%s %sis eating%s\n", WHE, philo_id, DEF, GRN, DEF);
	else if (indice == 's')
		printf("%s%d%s %sis sleeping%s\n", WHE, philo_id, DEF, CYN_F, DEF);
	else if (indice == 't')
		printf("%s%d%s %sis thinking%s\n", WHE, philo_id, DEF, MAA, DEF);
	pthread_mutex_unlock(write_lock);
}

void	philo_is_thinking(t_philo *philo)
{
	
	if ()
		*(philo->dead) = 1;
}

void	even_take_forks(t_philo *philo)
{
	pthread_mutex_lock(*(philo->r_fork));
	pthread_mutex_lock(*(philo->l_fork));
	ft_usleep(philo->time_to_eat);
	philo->eating = 1;
	if (philo->meals_eaten == 0)
		philo->start_time = get_current_time();
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(*(philo->r_fork));
	pthread_mutex_unlock(*(philo->r_fork));
}

void	odd_take_forks(t_philo *philo)
{
	pthread_mutex_lock(*(philo->l_fork));
	pthread_mutex_lock(*(philo->r_fork));
	ft_usleep(philo->time_to_eat);
	philo->eating = 1;
	if (philo->meals_eaten == 0)
		philo->start_time = get_current_time();
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(*(philo->l_fork));
	pthread_mutex_unlock(*(philo->r_fork));
}

void	routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->id % 2 != 0)
			odd_take_forks(philo);
		else
			even_take_forks(philo);
		pthread_mutex_lock(*(philo->meal_lock));
		philo->eating = 0;
		pthread_mutex_unlock(*(philo->meal_lock));
		ft_usleep(philo->time_to_sleep);
	}
}

int	main(int argc, char **argv)
{
	t_pgm			monitor;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	
	if (arguments_parsing(argc, argv) == -1
	 || init_all(argv, &forks, &philo, &monitor) == -1)
		return (-1);
	
	return (0);
}