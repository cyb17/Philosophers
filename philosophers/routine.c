/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:19:57 by yachen            #+#    #+#             */
/*   Updated: 2023/10/10 20:39:37 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

int	check_dead_flag(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

/*static void	action_time(t_philo *philo, size_t act_time)
{
	size_t	time1;
	size_t	time2;
	size_t	time3;

	time3 = get_current_time();
	while (get_current_time() - time3 < act_time)
	{
		time1 = get_current_time();
		if (check_dead_flag(philo) == 1)
			break ;
		time2 = get_current_time();
		ft_usleep(10 - (time2 - time1));
	}
}*/

/*static void	eating(t_philo *philo)
{
//	pthread_mutex_lock(philo->meal_lock);
//	if (check_dead_flag(philo) == 1)
//		return ;
	philo->eating = 1;
//	if (check_dead_flag(philo) == 1)
//		return ;
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
//	action_time(philo, philo->time_to_eat);
//	if (check_dead_flag(philo) == 1)
//		return ;
//	if (check_dead_flag(philo) == 1)
//		return ;
	philo->eating = 0;
//	if (check_dead_flag(philo) == 1)
//		return ;
//	pthread_mutex_unlock(philo->meal_lock);
}*/

static void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_msg(philo, 'f');
	pthread_mutex_lock(philo->l_fork);
	print_msg(philo, 'f');
	print_msg(philo, 'e');
	//eating(philo);
	philo->eating = 1;
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->time_to_eat);
//	action_time(philo, philo->time_to_eat);
	philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	ft_sleep(t_philo *philo)
{
//	if (check_dead_flag(philo) == 1)
//		return ;
	print_msg(philo, 's');
//	if (check_dead_flag(philo) == 1)
//		return ;
	ft_usleep(philo->time_to_sleep);
//	action_time(philo, philo->time_to_sleep);
//	if (check_dead_flag(philo) == 1)
//		return ;
}

static void	ft_think(t_philo *philo)
{
//	if (check_dead_flag(philo) == 1)
//		return ;
	print_msg(philo,'t');
//	if (check_dead_flag(philo) == 1)
//		return ;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (check_dead_flag(philo) == 0)
	{
		ft_eat(philo);
	//	if (check_dead_flag(philo) == 1)
	//		break ;
		ft_sleep(philo);
	//	if (check_dead_flag(philo) == 1)
	//		break ;
		ft_think(philo);
	//	if (check_dead_flag(philo) == 1)
	//		break ;
	}
	return (NULL);
}
