/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:04:33 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/03 11:04:33 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

unsigned long	get_time_ms(void)
{
	struct timeval	now;
	unsigned long	timestamp;

	gettimeofday(&now, NULL);
	timestamp = (now.tv_sec * 1000 + now.tv_usec / 1000);
	return (timestamp);
}

void	usleep_limit(unsigned long time_ms)
{
	unsigned long	act_start;

	act_start = get_time_ms();
	while ((get_time_ms() - act_start) < time_ms)
		usleep(200);
}
