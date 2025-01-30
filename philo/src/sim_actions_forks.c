/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_actions_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 17:07:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	acquire_forks(t_philo *philo)
{
	unsigned long	timestamp;

	handle_mutex(&philo->fork1->mutex, LOCK);
	timestamp = get_time_ms(philo->sim);
	printf(WHI "%ld\t\t%d\t" NC YEL "has taken a fork\n" NC, timestamp, philo->id);
	handle_mutex(&philo->fork2->mutex, LOCK);
	timestamp = get_time_ms(philo->sim);
	printf(WHI "%ld\t\t%d\t" NC YEL "has taken a fork\n" NC, timestamp, philo->id);
}

void	release_forks(t_philo *philo)
{
	handle_mutex(&philo->fork1->mutex, UNLOCK);
	handle_mutex(&philo->fork2->mutex, UNLOCK);
}