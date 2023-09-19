/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachen <yachen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 14:13:35 by yachen            #+#    #+#             */
/*   Updated: 2023/09/19 11:17:49 by yachen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../includes/philosophers.h"

/* convert current timestamp (seconds to milliseconds)
and print it. */
void	get_timestamp(void)
{
	struct timeval time;
	long long time_ms;
	
	gettimeofday(&time, NULL);
	time_ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	printf("%lld ", time_ms);
}