/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:25:53 by yachen            #+#    #+#             */
/*   Updated: 2023/09/13 14:59:35 by yachen           ###   ########.fr       */
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
	
}

int philo_ft_atoi(char *str);
int	check_digit(char **argv);
int	arguments_parsing(int argc, char **argv);

#endif