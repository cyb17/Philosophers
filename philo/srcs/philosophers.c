/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:29:01 by yachen            #+#    #+#             */
/*   Updated: 2023/09/16 14:35:25 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	timestamp(void)
{
	struct timeval time;
	long long time_ms;
	
	gettimeofday(&time, NULL);
	time_ms = time.tv_sec / 1000;
	printf("%lld ", time_ms);
}

static void	take_l_then_r(t_data *data, int *left_fork, int *right_fork)
{
	pthread_mutex_lock(&data->table.mutex[*left_fork]);
	timestamp();
	printf("%d has taken a fork\n", data->i);
	pthread_mutex_lock(&data->table.mutex[*right_fork]);
	timestamp();
	printf("%d has taken a fork\n", data->i);
	timestamp();
	printf("%d is eating\n", data->i);
	usleep(data->time_eat);
	pthread_mutex_unlock(&data->table.mutex[*right_fork]);
	pthread_mutex_unlock(&data->table.mutex[*left_fork]);
}

static void	take_r_then_l(t_data *data, int *left_fork, int *right_fork)
{
	pthread_mutex_lock(&data->table.mutex[*right_fork]);
	timestamp();
	printf("%d has taken a fork\n", data->i);
	pthread_mutex_lock(&data->table.mutex[*left_fork]);
	timestamp();
	printf("%d has taken a fork\n", data->i);
	timestamp();
	printf("%d is eating\n", data->i);
	usleep(data->time_eat);
	pthread_mutex_unlock(&data->table.mutex[*left_fork]);
	pthread_mutex_unlock(&data->table.mutex[*right_fork]);
}

static void	*routine(void *tmp)
{
	int		left_fork;
	int		right_fork;
	t_data	*data;
	
	data = NULL;
	data = (t_data *)tmp;
	left_fork = data->i + 1;
	right_fork = data->i;
	if (right_fork == data->nb_philo - 1)
		left_fork = 0;
	if (data->i % 2 != 0)
		take_l_then_r(data, &left_fork, &right_fork);
	else
		take_r_then_l(data, &left_fork, &right_fork);
	return (NULL);
}

static void	init_table(t_table *tb, int nb_philo)
{
	int	i;

	i = 0;
	tb->thread = (pthread_t *)malloc(sizeof(pthread_t) * nb_philo);
	tb->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) *nb_philo);
	while (i < nb_philo)
		pthread_mutex_init(&tb->mutex[i++], NULL);
	tb->fork = (int *)malloc(sizeof(int) * nb_philo);
	memset(tb->fork, 0, nb_philo);
}

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
	data->i = 0;
	init_table(&data->table, data->nb_philo);
}
static void	destroy_table(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->nb_philo)
	{
		pthread_detach(data->table.thread[j]);
		pthread_mutex_destroy(&data->table.mutex[j]);
		j++;
	}
	free(data->table.thread);
	free(data->table.mutex);
	free(data->table.fork);
}

int	main(int argc, char  **argv)
{
	t_data			data;
	
	if (arguments_parsing(argc, argv) == 0)
		return (0);
	init_data(&data, argv);
	while (data.i < data.nb_philo)
		pthread_create(&data.table.thread[data.i++], NULL, &routine, &data);
	int	j = 0;
	while (j < data.nb_philo)
		pthread_join(data.table.thread[j++], NULL);
	destroy_table(&data);
	return (0);
}