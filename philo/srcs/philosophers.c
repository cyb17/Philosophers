/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 13:29:01 by yachen            #+#    #+#             */
/*   Updated: 2023/09/15 17:02:24 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	taking_forks()

void	*routine(void *data)
{
	//pthread_mutex_lock(&data->mutex);
	taking_fork_left(data)
	taking_fork_right(data)
	//usleep(data->time_of_eat);
	//pthread_mutex_unlock(&data->mutex);
}

static void	init_data(t_data *data, char **argv)
{
	data->nb_of_philo = philo_ft_atoi(argv[1]);
	data->time_to_die = philo_ft_atoi(argv[2]);
	data->time_to_eat = philo_ft_atoi(argv[3]);
	data->time_to_sleep = philo_ft_atoi(argv[4]);
	if (argv[5])
		data->nb_time_musteat = philo_ft_atoi(argv[5]);
	else
		data->nb_time_musteat = 0;
	pthread_mutex_init(&data->mutex, NULL);
	data->thread = (t_thread *)malloc(sizeof(t_thread) * (philo_ft_atoi(argv[1])));
}

int	main(int argc, char  **argv)
{
	t_data			data;
	int				i;
	
	if (arguments_parsing(argc, argv) == 0)
		return (0);
	i = 0;
	init_data(&data, argv);
	while (i < data.nb_of_philo)
		pthread_create(&thread[i++], NULL, &routine, &data);
	i = 0;
	while (i < data.nb_of_philo)
		pthread_join(&thread[i++], NULL);
	pthread_mutex_destroy(&mutex);
}