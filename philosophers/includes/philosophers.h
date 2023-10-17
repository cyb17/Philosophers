/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 13:37:00 by yachen            #+#    #+#             */
/*   Updated: 2023/10/17 15:38:10 by yachen           ###   ########.fr       */
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
# define MAA "\e[95;1m"

# define PHILO_MAX 200

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
	int				nb_of_philos;
	int				nb_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*meal_lock;
	pthread_mutex_t	*dead_lock;
}					t_philo;

typedef struct s_pgm
{
	int				dead_flag;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	dead_lock;
	t_philo			*philos;
	pthread_mutex_t	*forks;
}					t_pgm;

int		arguments_parsing(int argc, char **argv);
int		init_1(char **av, t_philo **philo, t_pgm *pgm, pthread_mutex_t **fork);
int		init_all(char **av, pthread_mutex_t **fork, t_philo **ph, t_pgm *pgm);

// utils1
long	philo_ft_atoi(char *str);
void	clean_forks(pthread_mutex_t **fork, int nb_fork);
void	clean_all(t_pgm *pgm);
size_t	get_current_time(void);
int		ft_usleep(size_t milliseconds);

// utils2

//int		philo_is_dead(t_philo *philo, char indice);
void	print_msg(t_philo *philo, char indice);

void	run_monitor(t_pgm *pgm);
void	*routine(void *arg);
int		check_dead_flag(t_philo *philo);

#endif
