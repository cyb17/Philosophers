/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:31:45 by yachen            #+#    #+#             */
/*   Updated: 2023/09/28 17:38:56 by yachen           ###   ########.fr       */
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

int	philo_is_thinking(t_philo *philo, pthread_mutex_t *fork)
{
	int	err;
	
	print_msg(philo, 't');
	err = pthread_mutex_lock(fork);
	while (err == -1)
	{
		if (((get_current_time() - philo->start_time) > philo->time_to_die)
			|| ((get_current_time() - philo->last_meal) > philo->time_to_die))
		{
			pthread_mutex_lock(philo->dead_lock);
			*(philo->dead) = 1;
			print_msg(philo, 'd');
			pthread_mutex_unlock(philo->dead_lock);
			return (-1);
		}
		err = pthread_mutex_lock(fork);
	}
	return (0);
}

int	even_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg(philo, 'f');
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, 'f');
	print_msg(philo, 'e');
	ft_usleep(philo->time_to_eat);
	philo->eating = 1;
	if (philo->meals_eaten == 0)
		philo->start_time = get_current_time();
	philo->meals_eaten++;
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	print_msg(philo, 's');
	ft_usleep(philo->time_to_sleep);
	return (0);
}

int	odd_take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, 'f');
	pthread_mutex_lock(philo->r_fork);
	print_msg(philo, 'f');
	print_msg(philo, 'e');
	philo->eating = 1;
	philo->meals_eaten++;
	ft_usleep(philo->time_to_eat);
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	print_msg(philo, 's');
	ft_usleep(philo->time_to_sleep);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		odd_take_forks(philo);
	else
		even_take_forks(philo);
	return (NULL);
}

/*int	check_eaten_time(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].num_of_philos)
	{
		if (philo[0].num_times_to_eat != 0
			&& philo[i].meals_eaten == philo[0].num_times_to_eat)
			return (0);
		i++;
	}
	return (-1);
}*/

/*void	*ft_monitor(void *arg)
{
	t_pgm	*monitor;
	
	monitor = (t_pgm *)arg;
	while (1)
	{
		if ((monitor->dead_flag == 1) || (check_eaten_time(monitor->philos) == 0))
		{
			clean_all(monitor);
			break ;
		}
	}
	return (NULL);
}*/

int	main(int argc, char **argv)
{
	//pthread_t		monitor_thread;
	t_pgm			monitor;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				i;
	
	i = 0;
	//monitor_thread = 0;
	if (arguments_parsing(argc, argv) == -1
	 || init_all(argv, &forks, &philo, &monitor) == -1)
		return (-1);
	int j = 0;
	while (j < 6)
		printf("start time: %zu\n", philo[j++].start_time);
	while (i < philo[0].num_of_philos)
	{
		pthread_create(&philo[i].thread, NULL, &routine, &philo[i]);
		i++;
	}
	//pthread_create(&monitor_thread, NULL, &ft_monitor, &monitor);
	i = 0;
	while (i < philo[0].num_of_philos)
		pthread_join(philo[i++].thread, NULL);
	clean_all(&monitor);
	//pthread_join(monitor_thread, NULL);
	return (0);
}
