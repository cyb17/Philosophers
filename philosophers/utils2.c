/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:20:16 by yachen            #+#    #+#             */
/*   Updated: 2023/10/09 14:47:22 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

/*int	philo_is_dead(t_philo *philo, char indice)
{	
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead) == 1)
	{
		if (indice == 'r')
			pthread_mutex_unlock(philo->r_fork);
		else if (indice == 'l')
			pthread_mutex_unlock(philo->l_fork);
		else if (indice == 'b')
		{
			pthread_mutex_unlock(philo->r_fork);
			pthread_mutex_unlock(philo->l_fork);
		}
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}*/

void	print_msg(t_philo *philo, char indice)
{
	size_t	timestamp;

	pthread_mutex_lock(philo->write_lock);
	if (check_dead_flag(philo) == 1)
	{
		pthread_mutex_unlock(philo->write_lock);
		return ;
	}
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
	else if (indice == 'F')
		printf("%sall philosophers have eaten enough%s\n", CYN, DEF);
	pthread_mutex_unlock(philo->write_lock);
}
