/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:17:49 by yachen            #+#    #+#             */
/*   Updated: 2023/10/02 15:01:29 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

static int	check_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j]
			&& (argv[i][j] == ' ' || (argv[i][j] > 8 && argv[i][j] < 14)))
			j++;
		if (argv[i][j] == '\0')
			return (-1);
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

static int	check_number(char **argv)
{
	if (philo_ft_atoi(argv[1]) == 0 || philo_ft_atoi(argv[2]) == 0
		|| philo_ft_atoi(argv[3]) == 0 || philo_ft_atoi(argv[4]) == 0)
		return (-1);
	return (0);
}

int	arguments_parsing(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("The number of argument is not valid\n");
		return (-1);
	}
	else if (check_digit(argv) == -1 || check_number(argv) == -1)
	{
		printf("One of the arguments is not a correct positive number\n");
		return (-1);
	}
	return (0);
}
