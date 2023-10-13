/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:31:45 by yachen            #+#    #+#             */
/*   Updated: 2023/10/13 12:08:06 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

/* Create all threads */
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
