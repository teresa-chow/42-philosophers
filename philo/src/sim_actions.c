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
	if (!sim_active((*philo)->sim))
		return ;
	print_state(*philo, THINKING, (*philo)->id);
	return ;
}

void	act_eat(t_philo **philo)
{
	unsigned long	timestamp;

	if (!sim_active((*philo)->sim))
		return ;
	timestamp = get_time_ms() - ((*philo)->sim->start);
	print_state(*philo, EATING, (*philo)->id);
	(*philo)->last_meal = timestamp;
	if ((*philo)->sim->info.n_times_to_eat != -1)
		(*philo)->n_meals++;
	if (will_starve(philo, (*philo)->sim->info.time_to_eat))
		return ;
	usleep_limit((*philo)->sim->info.time_to_eat);
	if ((*philo)->n_meals == (*philo)->sim->info.n_times_to_eat)
		set_bool(&(*philo)->counter, &(*philo)->full, 1);
	return ;
}

void	act_sleep(t_philo **philo)
{
	if (!sim_active((*philo)->sim))
		return ;
	print_state(*philo, SLEEPING, (*philo)->id);
	if (will_starve(philo, (*philo)->sim->info.time_to_sleep))
		return ;
	usleep_limit((*philo)->sim->info.time_to_sleep);
	return ;
}

void	print_state(t_philo *philo, enum e_state state,	unsigned int id)
{
	unsigned long	timestamp;

	handle_mutex(&philo->sim->print, LOCK);
	timestamp = (get_time_ms() - philo->sim->start);
	if (sim_active(philo->sim))
	{
		if (state == THINKING)
			printf(WHI "%ld\t\t%d\t" NC CYA "is thinking\n" NC, timestamp, id);
		else if (state == FORK)
			printf(WHI "%ld\t\t%d\t" NC
				YEL "has taken a fork\n" NC, timestamp, id);
		else if (state == EATING)
			printf(WHI "%ld\t\t%d\t" NC GRN "is eating\n" NC, timestamp, id);
		else if (state == SLEEPING)
			printf(WHI "%ld\t\t%d\t" NC BLU "is sleeping\n" NC, timestamp, id);
		else if (state == STARVED)
		{
			printf(WHI "%ld\t\t%d\t" NC RED "died\n" NC, timestamp, id);
			usleep(10000);
		}
	}
	handle_mutex(&philo->sim->print, UNLOCK);
	return ;
}
