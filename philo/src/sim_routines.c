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

/*void	*main_routine(void *arg)
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
}*/

void	*philo_routine(void *arg) // TOO MANY LINES
{
	t_philo	*philo;
	int	check;

	philo = (t_philo *)arg;
	check = 0;
	while (philo->sim->active == 0)
		;
	while (philo->sim->active == 1) // REVIEW STOPPED HERE
	{
		if (philo->sim->active == 0)
			return (NULL);
		check = check_forks(philo->nb - 1, philo->sim);
		if (check)
		{
			acquire_forks(philo);
			act_eat(philo->sim->info, philo->nb, &philo);
			release_forks(philo);
		}
		if ((philo[philo->nb - 1].state == NONE)
			|| (philo[philo->nb - 1].state == EATING))
			act_sleep(philo->sim->info, philo->nb - 1, &philo);
		if ((philo[philo->nb - 1].state == NONE)
			|| (philo[philo->nb - 1].state == SLEEPING))
			act_think(philo->nb - 1, &philo);
		act_die(&philo->sim, philo->sim->info, philo->nb - 1, &philo);
	}
	return (NULL);
}
