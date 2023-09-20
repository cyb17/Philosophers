/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:37:00 by yachen            #+#    #+#             */
/*   Updated: 2023/09/20 14:11:31 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{	
	int					nb_philo;
	size_t				time_die;
	size_t				time_eat;
	size_t				time_sleep;
	int					nb_time_musteat;
	pthread_mutex_t		write_lock;
}				t_data;

typedef struct s_philo
{
	t_data				*data;
	int				philo_id;
	pthread_t			thread;
	pthread_mutex_t		mutex;
	int				fork;
	int				time_eaten;
}				t_philo;

int 	philo_ft_atoi(char *str);
int		check_digit(char **argv);
int		arguments_parsing(int argc, char **argv);
void	get_timestamp(void);

#endif
