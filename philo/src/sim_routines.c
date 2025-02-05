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

void	*main_routine(void *arg)
{
	t_sim	*sim;
	unsigned int	i;

	sim = (t_sim *)arg;
	while (!sim_active(sim))
		;
	i = 0;
	while (sim_active(sim))
	{
		starvation_checker(sim, i);
		i++;
		if (i == sim->info.n_philo)
			i = 0;
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!sim_active(philo->sim))
		;
	if (philo->id % 2 != 0)
	{
		act_think(&philo);
		usleep(50);
	}
	while (sim_active(philo->sim))
	{
		act_eat(&philo);
		act_sleep(&philo);
		act_think(&philo);
	}
	handle_mutex(&philo->mutex, LOCK);
	if (philo->state != STARVED)
		philo->state = NONE;
	handle_mutex(&philo->mutex, UNLOCK);
	return (NULL);
}