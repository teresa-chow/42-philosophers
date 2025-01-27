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

	sim = (t_sim *)arg;
	while (sim->active == 0)
	{
		if (sim->active == 1)
			break ;
	}
	while (sim->active == 1)
	{
		if (sim->active == 0)
			end_simulation(&(*sim));
	}
	return (NULL);
}

void	*philo_routine(void *arg) // TOO MANY LINES
{
	t_philo	*philo;
	int	check;

	philo = (t_philo *)arg;
	check = 0;
	while (philo->sim->active == 0)
	{
		if (philo->sim->active == 1)
			break ;
	}
	while (philo->sim->active == 1)
	{
		if (philo->sim->active == 0)
			return (NULL);
		check = check_forks(philo->index, philo->sim);
		if (check)
		{
			acquire_forks(philo);
			act_eat(philo->sim->info, philo->index, &philo);
			release_forks(philo);
		}
		if ((philo[philo->index].state == NONE)
			|| (philo[philo->index].state == EATING))
			act_sleep(philo->sim->info, philo->index, &philo);
		if ((philo[philo->index].state == NONE)
			|| (philo[philo->index].state == SLEEPING))
			act_think(philo->index, &philo);
		act_die(&philo->sim, philo->sim->info, philo->index, &philo);
	}
	return (NULL);
}
