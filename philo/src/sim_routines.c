/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_routines.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 17:07:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!sim_active(philo->sim))
		;
	philo->start = get_time_ms();
	if (philo->id % 2 == 0)
		act_think(&philo);
	while (sim_active(philo->sim))
	{
		acquire_forks(&philo);
		act_eat(&philo);
		release_forks(&philo);
		act_sleep(&philo);
		act_think(&philo);
	}
	return (NULL);
}

void	*single_routine(void *arg)
{
	t_philo			*philo;
	unsigned long	timestamp;

	philo = (t_philo *)arg;
	philo->start = get_time_ms();
	timestamp = get_time_ms() - philo->start;
	printf(WHI "%ld\t\t%d\t" NC CYA "is thinking\n" NC, timestamp, 1);
	printf(WHI "%ld\t\t%d\t" NC
		YEL "has taken a fork\n" NC, timestamp, 1);
	usleep(philo->sim->info.time_to_die * 1000);
	timestamp = get_time_ms() - philo->start;
	printf(WHI "%ld\t\t%d\t" NC RED "has died\n" NC, timestamp, 1);
	return (NULL);
}
