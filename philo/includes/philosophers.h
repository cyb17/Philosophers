/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:25:53 by yachen            #+#    #+#             */
/*   Updated: 2023/09/16 13:39:05 by yachen           ###   ########.fr       */
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

//# define NB_MAX_PROCESS 30872

typedef struct s_table
{
	pthread_t		*thread;
	pthread_mutex_t	*mutex;
	int				*fork;
}				t_table;

typedef struct s_data
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nb_time_musteat;
	int				i;
	t_table			table;
}				t_data;

int philo_ft_atoi(char *str);
int	check_digit(char **argv);
int	arguments_parsing(int argc, char **argv);

#endif