/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 17:07:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	act_think(t_philo **philo)
{
	unsigned long	timestamp;

	if (get_bool(&(*philo)->sim->status, &(*philo)->sim->active) == 0)
		return ;
	(*philo)->state = THINKING;
	timestamp = get_time_ms((*philo)->sim);
	handle_mutex(&(*philo)->sim->time, UNLOCK);
	printf(WHI "%ld\t\t%d\t" NC CYA "is thinking\n" NC, timestamp, (*philo)->id);
	return ;
}

void	act_eat(t_philo **philo)
{
	unsigned long	timestamp;

	if (get_bool(&(*philo)->sim->status, &(*philo)->sim->active) == 0)
		return ;
	(*philo)->state = EATING;
	timestamp = get_time_ms((*philo)->sim);
	handle_mutex(&(*philo)->sim->time, UNLOCK);
	(*philo)->last_meal = timestamp;
	printf(WHI "%ld\t\t%d\t" NC GRN "is eating\n" NC, timestamp, (*philo)->id);
	usleep((*philo)->sim->info.time_to_eat);
	(*philo)->n_meals++;
	return ;
}

void	act_sleep(t_philo **philo)
{
	unsigned long	timestamp;

	if (get_bool(&(*philo)->sim->status, &(*philo)->sim->active) == 0)
		return ;
	(*philo)->state = SLEEPING;
	timestamp = get_time_ms((*philo)->sim);
	handle_mutex(&(*philo)->sim->time, UNLOCK);
	printf(WHI "%ld\t\t%d\t" NC BLU "is sleeping\n" NC, timestamp, (*philo)->id);
	usleep((*philo)->sim->info.time_to_sleep);
	return ;
}

void	act_die(t_philo **philo)
{
	unsigned long	timestamp;

	if (get_bool(&(*philo)->sim->status, &(*philo)->sim->active) == 0)
		return ;
	timestamp = get_time_ms((*philo)->sim);
	handle_mutex(&(*philo)->sim->time, UNLOCK);
	if ((timestamp - (*philo)->last_meal) > ((*philo)->sim->info.time_to_die / 1000))
	{
		(*philo)->state = STARVED;
		printf(WHI "%ld\t\t%d\t" NC RED "has died\n" NC, timestamp, (*philo)->id);
		set_bool(&(*philo)->sim->status, &(*philo)->sim->active, 0);
	}
	return ;
}