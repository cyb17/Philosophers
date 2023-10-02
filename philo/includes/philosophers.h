/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:37:00 by yachen            #+#    #+#             */
/*   Updated: 2023/10/02 10:27:26 by yachen           ###   ########.fr       */
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

# define DEF "\e[0m"
# define RED "\e[91m"
# define GRN "\e[92m"
# define YEW "\e[93m"
# define WHE "\e[97m"
# define CYN "\e[96m"
# define CYN_F "\e[36;1m"
# define MAA_F "\e[35;1m"
# define MAA "\e[95;1m"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	int				*meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	int				eat_meal_time;
	//pthread_mutex_t	dead_lock;
	//pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}					t_pgm;

int		arguments_parsing(int argc, char **argv);
int		init_all(char **av, pthread_mutex_t **fork, t_philo **philo, t_pgm *mnt);

// utils1
int 	philo_ft_atoi(char *str);
void	clean_forks(pthread_mutex_t **fork, int nb_fork);
void	clean_monitor(t_pgm *monitor);
void	clean_all(t_pgm *monitor);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

#endif
