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

static void	acquire_forks_even(t_philo **philo);
static void	acquire_forks_odd(t_philo **philo);

void	acquire_forks(t_philo **philo)
{
	if (!sim_active((*philo)->sim))
		return ;
	if ((*philo)->id % 2 == 0)
		acquire_forks_even(philo);
	else
		acquire_forks_odd(philo);
	return ;
}

static void	acquire_forks_even(t_philo **philo)
{
	unsigned long	timestamp;

	handle_mutex(&(*philo)->fork1->mutex, LOCK);
	timestamp = get_time_ms((*philo)->sim);
	print_state((*philo)->sim, FORK, timestamp, (*philo)->id);
	handle_mutex(&(*philo)->fork2->mutex, LOCK);
	timestamp = get_time_ms((*philo)->sim);
	print_state((*philo)->sim, FORK, timestamp, (*philo)->id);

}

static void	acquire_forks_odd(t_philo **philo)
{
	unsigned long	timestamp;

	handle_mutex(&(*philo)->fork2->mutex, LOCK);
	timestamp = get_time_ms((*philo)->sim);
	print_state((*philo)->sim, FORK, timestamp, (*philo)->id);
	handle_mutex(&(*philo)->fork1->mutex, LOCK);
	timestamp = get_time_ms((*philo)->sim);
	print_state((*philo)->sim, FORK, timestamp, (*philo)->id);
}

void	release_forks(t_philo **philo)
{
	if ((*philo)->id % 2 == 0)
	{
		handle_mutex(&(*philo)->fork1->mutex, UNLOCK);
		handle_mutex(&(*philo)->fork2->mutex, UNLOCK);
	}
	else
	{
		handle_mutex(&(*philo)->fork2->mutex, UNLOCK);
		handle_mutex(&(*philo)->fork1->mutex, UNLOCK);
	}
}