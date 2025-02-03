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

static void	change_state(t_philo **philo, enum e_state state);
static void	print_state(pthread_mutex_t *mutex, enum e_state state,
		unsigned long timestamp, unsigned int id);

void	act_think(t_philo **philo)
{
	unsigned long	timestamp;

	if (!sim_active((*philo)->sim))
		return ;
	change_state(philo, THINKING);
	timestamp = get_time_ms((*philo)->sim);
	print_state(&(*philo)->sim->print, THINKING, timestamp, (*philo)->id);
	return ;
}

void	act_eat(t_philo **philo)
{
	unsigned long	timestamp;

	if (!sim_active((*philo)->sim))
		return ;
	change_state(philo, EATING);
	timestamp = get_time_ms((*philo)->sim);
	(*philo)->last_meal = timestamp;
	print_state(&(*philo)->sim->print, EATING, timestamp, (*philo)->id);
	usleep_limit((*philo)->sim->info.time_to_eat, (*philo)->sim);
	if ((*philo)->sim->info.n_times_to_eat != -1)
	{
		(*philo)->n_meals++;
		if ((*philo)->n_meals == (*philo)->sim->info.n_times_to_eat)
			(*philo)->full = 1;
	}
	return ;
}

void	act_sleep(t_philo **philo)
{
	unsigned long	timestamp;

	if (!sim_active((*philo)->sim))
		return ;
	change_state(philo, SLEEPING);
	timestamp = get_time_ms((*philo)->sim);
	print_state(&(*philo)->sim->print, SLEEPING, timestamp, (*philo)->id);
	usleep_limit((*philo)->sim->info.time_to_sleep, (*philo)->sim);
	return ;
}

void	act_die(t_philo **philo)
{
	unsigned long	timestamp;

	if (!sim_active((*philo)->sim))
		return ;
	timestamp = get_time_ms((*philo)->sim);
	if ((timestamp - (*philo)->last_meal) > ((*philo)->sim->info.time_to_die))
	{
		change_state(philo, STARVED);
		print_state(&(*philo)->sim->print, STARVED, timestamp, (*philo)->id);
		set_bool(&(*philo)->sim->status, &(*philo)->sim->active, 0);
	}
	return ;
}

static void	change_state(t_philo **philo, enum e_state state)
{
	handle_mutex(&(*philo)->sim->checker, LOCK);
	(*philo)->state = state;
	handle_mutex(&(*philo)->sim->checker, UNLOCK);
}

static void	print_state(pthread_mutex_t *mutex, enum e_state state,
		unsigned long timestamp, unsigned int id)
{
	handle_mutex(mutex, LOCK);
	if (state == THINKING)
		printf(WHI "%ld\t\t%d\t" NC CYA "is thinking\n" NC, timestamp, id);
	else if (state == EATING)
		printf(WHI "%ld\t\t%d\t" NC GRN "is eating\n" NC, timestamp, id);
	else if (state == SLEEPING)
		printf(WHI "%ld\t\t%d\t" NC BLU "is sleeping\n" NC, timestamp, id);
	else if (state == STARVED)
		printf(WHI "%ld\t\t%d\t" NC RED "has died\n" NC, timestamp, id);
	handle_mutex(mutex, UNLOCK);
}