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

bool	starvation_checker(t_sim *sim, unsigned int i)
{
	handle_mutex(&sim->checker, LOCK);
	if (sim->philo[i].state == STARVED)
    {
		set_bool(&sim->status, &sim->active, 0);
		handle_mutex(&sim->checker, UNLOCK);
		return (1);
    }
	handle_mutex(&sim->checker, UNLOCK);
	return (0);
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
		handle_mutex(&sim->forks[i].mutex, DESTROY);
		i++;
	}
	free(sim->forks);
	if (sim->philo)
		free(sim->philo);
	handle_mutex(&sim->checker, DESTROY);
	handle_mutex(&sim->print, DESTROY);
	handle_mutex(&sim->status, DESTROY);
}
