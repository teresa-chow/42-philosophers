/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_end.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:13:08 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/03 11:13:08 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

bool	will_starve(t_philo **philo, unsigned long act_time_ms)
{
	unsigned long	timestamp;
	unsigned long	remaining;
	unsigned long	finish;

	if (!sim_active((*philo)->sim))
		return (0);
	timestamp = get_time_ms((*philo)->sim);
	finish = timestamp + act_time_ms;
	if ((finish - (*philo)->last_meal) > ((*philo)->sim->info.time_to_die))
	{
		remaining = ((*philo)->last_meal + (*philo)->sim->info.time_to_die)
			- timestamp;
		usleep_limit(remaining, (*philo)->sim);
		set_bool(&(*philo)->state, &(*philo)->starved, 1);
		return (1);
	}
	return (0);
}

void	starvation_checker(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	if (sim_active(sim))
	{
		while (i < sim->info.n_philo)
		{
			if (get_bool(&sim->philo[i].state, &sim->philo[i].starved) == 1)
			{
				print_state(sim, STARVED, sim->philo[i].id);
				set_bool(&sim->status, &sim->active, 0);
				return ;
			}
			i++;
		}
	}
	return ;
}

void	philos_full_checker(t_sim *sim)
{
	unsigned int	i;
	bool			full;

	i = 0;
	full = 1;
	if (sim_active(sim))
	{
		while (i < sim->info.n_philo)
		{
			if (!get_bool(&sim->philo[i].counter, &sim->philo[i].full))
				full = 0;
			i++;
		}
		if (full == 1)
		{
			print_philos_full(sim);
			set_bool(&sim->status, &sim->active, 0);
		}
	}
	return ;
}

bool	sim_active(t_sim *sim)
{
	return (get_bool(&sim->status, &sim->active));
}

void	end_sim(t_sim *sim)
{
	unsigned int	i;
	
	i = 0;
	while (i < sim->info.n_philo)
	{
		handle_thread(&sim->philo[i].thread, NULL, NULL, JOIN);
		i++;
	}
	i = 0;
	while (i < sim->info.n_philo)
	{
		handle_mutex(&sim->forks[i], DESTROY);
		handle_mutex(&sim->philo[i].state, DESTROY);
		handle_mutex(&sim->philo[i].counter, DESTROY);
		i++;
	}
	free(sim->forks);
	if (sim->philo)
		free(sim->philo);
	handle_mutex(&sim->print, DESTROY);
	handle_mutex(&sim->status, DESTROY);
}
