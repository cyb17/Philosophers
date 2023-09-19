/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:39:35 by yachen            #+#    #+#             */
/*   Updated: 2023/09/19 17:05:42 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	init_data(t_data *data, char **argv)
{
	data->nb_philo = philo_ft_atoi(argv[1]);
	data->time_die = philo_ft_atoi(argv[2]);
	data->time_eat = philo_ft_atoi(argv[3]);
	data->time_sleep = philo_ft_atoi(argv[4]);
	if (argv[5])
		data->nb_time_musteat = philo_ft_atoi(argv[5]);
	else
		data->nb_time_musteat = 0;
}

static t_philo	*init_philo(char **argv)
{
	int	i;
	int	nb_philo;
	t_philo	*philo;

	i = 0;
	nb_philo = philo_ft_atoi(argv[1]);
	philo = (t_philo *)malloc(sizeof(t_philo) * nb_philo);
	if (!philo)
		return (NULL);
	while (i < nb_philo)
	{
		init_data(&philo[i].data, argv);
		philo[i].philo_id = i + 1;
		philo[i].thread = 0;
		if (pthread_mutex_init(&philo[i].mutex, NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&philo[i].mutex);
			return (NULL);
		}
		philo[i].fork = 0;
		philo[i].time_eaten = 0;
		i++;
	}
	return (philo);
}
static void	clean_all(t_philo *philo, size_t indice)
{
	size_t	i;

	i = 0;
	while (i < philo->data.nb_philo)
	{
		if (i < indice)
			pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&philo[i].mutex);
		i++;
	}
	free(philo);
}
static int	test_fork_dispo(t_philo *philo)
{
	if (philo->fork == 0 && philo[1].fork == 0)
		return (0);
	else
		return (-1);
}

static void	*take_l_then_r(void *arg)
{
	t_philo *philo;
	int		flag;
	
	flag = 0;
	philo = (t_philo *)arg;
	while (test_fork_dispo(philo) == -1)
	{
		if (flag == 0)
		{
			get_timestamp();
			printf("%zu is thinking\n", philo->philo_id);
			flag = 1;
		}
		test_fork_dispo(philo);
	}
	pthread_mutex_lock(&philo->mutex);
	philo->fork = 1;
	philo[1].fork = 1;
	get_timestamp();
	printf("%zu has taken a fork\n", philo->philo_id);
	pthread_mutex_lock(&philo[1].mutex);
	get_timestamp();
	printf("%zu has taken a fork\n", philo->philo_id);
	get_timestamp();
	printf("%zu is eating\n", philo->philo_id);
	usleep(philo->data.time_eat);
	philo->fork = 0;
	philo[1].fork = 0;
	get_timestamp();
	printf("%zu is sleeping\n", philo->philo_id);
	pthread_mutex_unlock(&philo[1].mutex);
	pthread_mutex_unlock(&philo->mutex);
	return (NULL);
}

static void	*take_r_then_l(void *arg)
{
	t_philo *philo;
	int		flag;
	
	flag = 0;
	philo = (t_philo *)arg;
	while (test_fork_dispo(philo) == -1)
	{
		if (flag == 0)
		{
			get_timestamp();
			printf("%zu is thinking\n", philo->philo_id);
			flag = 1;
		}
		test_fork_dispo(philo);
	}
	pthread_mutex_lock(&philo[1].mutex);
	philo->fork = 1;
	philo[1].fork = 1;
	get_timestamp();
	printf("%zu has taken a fork\n", philo->philo_id);
	pthread_mutex_lock(&philo->mutex);
	get_timestamp();
	printf("%zu has taken a fork\n", philo->philo_id);
	get_timestamp();
	printf("%zu is eating\n", philo->philo_id);
	usleep(philo->data.time_eat);
	philo->fork = 0;
	philo[1].fork = 0;
	get_timestamp();
	printf("%zu is sleeping\n", philo->philo_id);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo[1].mutex);
	return (NULL);
}

static int	create_thread(pthread_t *thread, size_t i, t_philo *philo)
{
	int	err;

	err = 0;
	if ((i + 1) % 2 != 0)
		err = pthread_create(thread, NULL, &take_l_then_r, philo);
	else
		err = pthread_create(thread, NULL, &take_r_then_l, philo);
	if (err != 0)
		return (-1);
	return (0);
}

int	main(int argc, char  **argv)
{
	t_philo	*philo;
	size_t		i;
	
	if (arguments_parsing(argc, argv) == -1)
		return (1);
	philo = init_philo(argv);
	if (!philo)
		return (1);
	i = 0;
	while (i < philo->data.nb_philo)
	{
		if (create_thread(&philo[i].thread, i, &philo[i]) == -1)
		{
			clean_all(philo, i);
			return (1);
		}
		i++;
	}
	clean_all(philo, i);
	return (0);
}
