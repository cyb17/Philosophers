/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:20:16 by yachen            #+#    #+#             */
/*   Updated: 2023/10/13 10:39:26 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

/* Write nothing if a philo is dead */
/*void	print_msg(t_philo *philo, char indice)
{
	size_t	timestamp;

	pthread_mutex_lock(philo->write_lock);
	if (check_dead_flag(philo) == 1)
	{
		pthread_mutex_unlock(philo->write_lock);
		return ;
	}
	timestamp = get_current_time() - philo->start_time;
	printf("%zu ", timestamp);
	//printf("%s%zu%s ", WHE, timestamp, DEF);
	if (indice == 'f')
		printf("%s%d%s %shas taken a fork%s\n", WHE, philo->id, DEF, YEW, DEF);
	else if (indice == 'e')
		printf("%s%d%s %sis eating%s\n", WHE, philo->id, DEF, GRN, DEF);
	else if (indice == 's')
		printf("%s%d%s %sis sleeping%s\n", WHE, philo->id, DEF, CYN_F, DEF);
	else if (indice == 't')
		printf("%s%d%s %sis thinking%s\n", WHE, philo->id, DEF, MAA, DEF);
	else if (indice == 'd')
		printf("%s%d%s %sis died%s\n", WHE, philo->id, DEF, RED, DEF);
	else if (indice == 'F')
		printf("%sall philosophers have eaten enough%s\n", CYN, DEF);
	pthread_mutex_unlock(philo->write_lock);
}*/

/* Version without text color for phisolophers's tester */
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
	printf("%zu ", timestamp);
	if (indice == 'f')
		printf("%d has taken a fork\n", philo->id);
	else if (indice == 'e')
		printf("%d is eating\n", philo->id);
	else if (indice == 's')
		printf("%d is sleeping\n", philo->id);
	else if (indice == 't')
		printf("%d is thinking\n", philo->id);
	else if (indice == 'd')
		printf("%d is died\n", philo->id);
	else if (indice == 'F')
		printf("all philosophers have eaten enough\n");
	pthread_mutex_unlock(philo->write_lock);
}
