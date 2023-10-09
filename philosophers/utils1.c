/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:13:35 by yachen            #+#    #+#             */
/*   Updated: 2023/10/09 14:32:28 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "./includes/philosophers.h"

int	philo_ft_atoi(char *str)
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

void	clean_all(t_pgm *pgm)
{
	pthread_mutex_destroy(&pgm->write_lock);
	clean_forks(&pgm->meal_lock, pgm->philos[0].nb_of_philos);
	pthread_mutex_destroy(&pgm->dead_lock);
	clean_forks(&pgm->forks, pgm->philos[0].nb_of_philos);
	free(pgm->meal_lock);
	free(pgm->forks);
	free(pgm->philos);
}

// Gets the current time in milliseconds
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/* Improved version of sleep function, allows you to wait a certain number
 of milliseconds without completely blocking the program */
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
