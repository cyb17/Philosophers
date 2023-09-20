/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:39:35 by yachen            #+#    #+#             */
/*   Updated: 2023/09/20 14:12:34 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	init_data(t_data *data, char **argv)
{
	data->nb_philo = philo_ft_atoi(argv[1]);
	data->time_die = philo_ft_atoi(argv[2]);
	data->time_eat = philo_ft_atoi(argv[3]);
	data->time_sleep = philo_ft_atoi(argv[4]);
	if (argv[5])
		data->nb_time_musteat = philo_ft_atoi(argv[5]);
	else
		data->nb_time_musteat = 0;
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		printf("write_lock Mutex failed\n");
		return (-1);
	}
	return (0);
}

static int	init_philo(t_philo **philo, t_data *data, char **argv)
{
	int	i;

	i = 0;
	if (init_data(data, argv) == -1)
		return (-1);
	*philo = (t_philo *)malloc(sizeof(t_philo) * data->nb_philo);
	if (!(*philo))
		return (-1);
	while (i < (int)data->nb_philo)
	{
		(*philo)[i].data = data;
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].thread = 0;
		if (pthread_mutex_init(&((*philo)[i].mutex), NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&((*philo)[i].mutex));
			free(*philo);
			return (-1);
		}
		(*philo)[i].fork = 0;
		(*philo)[i].time_eaten = 0;
		i++;
	}
	return (0);
}
static void	clean_all(t_philo *philo, int indice)
{
	int	i;

	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (i < indice)
			pthread_join(philo[i].thread, NULL);
		pthread_mutex_destroy(&philo[i].mutex);
		i++;
	}
	free(philo);
}

static void	print_msg(char indice, size_t philo_id, pthread_mutex_t *write_lock)
{
	pthread_mutex_lock(write_lock);
	get_timestamp();
	if (indice == 'f')
		printf("%zu has taken a fork\n", philo_id);
	else if (indice == 'e')
		printf("%zu is eating\n", philo_id);
	else if (indice == 's')
		printf("%zu is sleeping\n", philo_id);
	else if (indice == 't')
		printf("%zu is thinking\n", philo_id);
	pthread_mutex_unlock(write_lock);
}
static int	test(t_philo *philo)
{
	if (philo->fork == 0 && philo[1].fork == 0)
		return (0);
	else
		return (-1);
}
static void	test_fork_dispo(t_philo *philo)
{
	int		flag;
	
	flag = 0;
	while (test(philo) == -1)
	{
		if (flag == 0)
		{
			print_msg('t', philo->philo_id, &philo->data->write_lock);
			flag = 1;
		}
		test(philo);
	}
}

static void	*take_l_then_r(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	test_fork_dispo(philo);
	pthread_mutex_lock(&philo->mutex);
	philo->fork = 1;
	philo[1].fork = 1;
	print_msg('f', philo->philo_id, &philo->data->write_lock);
	pthread_mutex_lock(&philo[1].mutex);
	print_msg('f', philo->philo_id, &philo->data->write_lock);
	print_msg('e', philo->philo_id, &philo->data->write_lock);
	usleep(philo->data->time_eat);
	philo->fork = 0;
	philo[1].fork = 0;
	print_msg('s', philo->philo_id, &philo->data->write_lock);
	pthread_mutex_unlock(&philo[1].mutex);
	pthread_mutex_unlock(&philo->mutex);
	return (NULL);
}

static void	*take_r_then_l(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	test_fork_dispo(philo);
	pthread_mutex_lock(&philo[1].mutex);
	philo->fork = 1;
	philo[1].fork = 1;
	print_msg('f', philo->philo_id, &philo->data->write_lock);
	pthread_mutex_lock(&philo->mutex);
	print_msg('f', philo->philo_id, &philo->data->write_lock);
	print_msg('e', philo->philo_id, &philo->data->write_lock);
	usleep(philo->data->time_eat);
	philo->fork = 0;
	philo[1].fork = 0;
	print_msg('s', philo->philo_id, &philo->data->write_lock);
	pthread_mutex_unlock(&philo->mutex);
	pthread_mutex_unlock(&philo[1].mutex);
	return (NULL);
}

static int	create_thread(int i, t_philo *philo, t_philo last_philo[])
{
	int	err;

	err = 0;
	if ((i + 1) % 2 != 0)
	{
		if (i + 1 == philo->data->nb_philo)
			err = pthread_create(&philo[i].thread, NULL, &take_l_then_r, &last_philo);
		else
			err = pthread_create(&philo[i].thread, NULL, &take_l_then_r, &philo[i]);
	}
	else
	{
		if (i + 1 == philo->data->nb_philo)
			err = pthread_create(&philo[i].thread, NULL, &take_r_then_l, &last_philo);
		else
			err = pthread_create(&philo[i].thread, NULL, &take_r_then_l, &philo[i]);
	}
	if (err != 0)
		return (-1);
	return (0);
}

int	main(int argc, char  **argv)
{
	t_data		data;
	t_philo		*philo;
	t_philo		last_philo[2];
	int			i;
	
	philo = NULL;
	if (arguments_parsing(argc, argv) == -1
		|| init_philo(&philo, &data, argv) == -1)
		return (1);
	last_philo[0] = philo[philo->data->nb_philo - 1];
	last_philo[1] = philo[0];
	i = 0;
	while (i < philo->data->nb_philo)
	{
		if (create_thread(i, philo, last_philo) == -1)
		{
			clean_all(philo, i);
			return (1);
		}
		i++;
	}
	clean_all(philo, i);
	return (0);
}
