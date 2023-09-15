/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:25:53 by yachen            #+#    #+#             */
/*   Updated: 2023/09/15 16:17:59 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>

//# define NB_MAX_PROCESS 30872

typedef struct s_thread
{
	pthread_t	thread;
	int			fork;
	void		*ptr_fork;
}				t_thread;

typedef struct s_data
{
	int				nb_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_time_musteat;
	pthread_mutex_t	mutex;
	t_thread		*thread;
}				t_data;

int philo_ft_atoi(char *str);
int	check_digit(char **argv);
int	arguments_parsing(int argc, char **argv);

#endif