/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:31:45 by yachen            #+#    #+#             */
/*   Updated: 2023/10/02 10:49:03 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	print_msg(t_philo *philo, char indice)
{
	size_t	timestamp;
	
	pthread_mutex_lock(philo->write_lock);
	timestamp = get_current_time() - philo->start_time;
	printf("%s%zu%s ", WHE, timestamp, DEF);
	if (indice == 'f')
		printf("%s%d%s %shas taken a fork%s\n", WHE, philo->id, DEF, YEW, DEF);
	else if (indice == 'e')
		printf("%s%d%s %sis eating%s\n", WHE, philo->id, DEF, GRN, DEF);
	else if (indice == 's')
		printf("%s%d%s %sis sleeping%s\n", WHE, philo->id, DEF, CYN_F, DEF);
	else if (indice == 't')
		printf("%s%d%s %sis thinking%s\n", WHE, philo->id, DEF, MAA, DEF);
	else if (indice == 'd')
		printf("%s%d%s %sis dead%s\n", WHE, philo->id, DEF, RED, DEF);
	pthread_mutex_unlock(philo->write_lock);
}

void	even_take_forks(t_philo *philo)
{
	if (*(philo->dead) == 1)
		return ;
	pthread_mutex_lock(philo->r_fork);
	print_msg(philo, 'f');
	if (*(philo->dead) == 1)
		return ;
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, 'f');
	print_msg(philo, 'e');
	if (*(philo->dead) == 1)
		return ;
	philo->eating = 1;
	philo->last_meal = get_current_time();
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->num_times_to_eat)
		(*philo->meal)++;
	if (*(philo->dead) == 1)
		return ;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	if (*(philo->dead) == 1)
		return ;
}

void	odd_take_forks(t_philo *philo)
{
	if (*(philo->dead) == 1)
		return ;
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, 'f');
	if (*(philo->dead) == 1)
		return ;
	pthread_mutex_lock(philo->r_fork);
	print_msg(philo, 'f');
	print_msg(philo, 'e');
	if (*(philo->dead) == 1)
		return ;
	philo->eating = 1;
	philo->last_meal = get_current_time();
	ft_usleep(philo->time_to_eat);
	philo->meals_eaten++;
	if (philo->meals_eaten == philo->num_times_to_eat)
		(*philo->meal)++;
	if (*(philo->dead) == 1)
		return ;
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
	if (*(philo->dead) == 1)
		return ;
}

int	check_philo_death(t_philo *philo)
{
	if ((((get_current_time() - philo->start_time) > philo->time_to_die)
		&& ((get_current_time() - philo->last_meal) > philo->time_to_die))
		|| (*(philo->meal) == philo->num_of_philos))
	{
		*(philo->dead) = 1;
		print_msg(philo, 'd');
		return (1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (*(philo->dead) == 0)
	{
		if (philo->id % 2 != 0)
			odd_take_forks(philo);
		else
			even_take_forks(philo);
		if (*(philo->dead) == 1)
			return (NULL);
		philo->eating = 0;
		print_msg(philo, 's');
		ft_usleep(philo->time_to_sleep);
		if (*(philo->dead) == 1)
			return (NULL);
		print_msg(philo, 't');
		if (*(philo->dead) == 1)
			return (NULL);
		if (check_philo_death(philo) == 1)
			return (NULL);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_pgm			monitor;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				i;
	int				j;
	
	i = 0;
	if (arguments_parsing(argc, argv) == -1
	 || init_all(argv, &forks, &philo, &monitor) == -1)
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
	clean_all(&monitor);
	return (0);
}
