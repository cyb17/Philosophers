/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:17:49 by yachen            #+#    #+#             */
/*   Updated: 2023/09/19 15:35:15 by yachen           ###   ########.fr       */
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
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	arguments_parsing(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("The number of argument is not valid\n");
		return (-1);
	}
	else if (check_digit(argv) == -1)
	{
		printf("One of the arguments is not a correct positive number\n");
		return (-1);
	}
	return (0);
}