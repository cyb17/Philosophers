/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:17:49 by yachen            #+#    #+#             */
/*   Updated: 2023/09/13 14:59:23 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int philo_ft_atoi(char *str)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	while (str[i] && (str[i] == ' ' || ((str[i] > 8 && str[i] < 14))))
		i++;
	while (str[i] <= '9' && str[i] >= '0')
	{
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	return (nb);
}

int	check_digit(char **argv)
{
	int	i;
	int	j;
	
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	arguments_parsing(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("The number of argument is not valid\n");
		return (0);
	}
	else if (check_digit(argv) == 0)
	{
		printf("One of the arguments is not a correct positive number\n");
		return (0);
	}
	/*else if (philo_ft_atoi(argv[1]) > NB_MAX_PROCESS)
	{
		printf("You have exceeded the max number ");
		printf("of processes that this computer can execute\n");
		return (0);
	}*/
	return (1);
}