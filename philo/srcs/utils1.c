/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:13:35 by yachen            #+#    #+#             */
/*   Updated: 2023/09/28 16:51:07 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/philosophers.h"

int philo_ft_atoi(char *str)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] == ' ' || ((str[i] > 8 && str[i] < 14))))
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

void	clean_forks(pthread_mutex_t **fork, int nb_fork)
{
	int	i;

	i = 0;
	while (i < nb_fork)
		pthread_mutex_destroy(&(*fork)[i++]);
}

void	clean_monitor(t_pgm *monitor)
{
	pthread_mutex_destroy(&monitor->dead_lock);
	pthread_mutex_destroy(&monitor->meal_lock);
	pthread_mutex_destroy(&monitor->write_lock);
}

void	clean_all(t_pgm *monitor)
{
	clean_monitor(monitor);
	clean_forks(&monitor->forks, monitor->philos[0].num_of_philos);
	free(monitor->forks);
	free(monitor->philos);
}

// Gets the current time in milliseconds
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// Improved version of sleep function
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}