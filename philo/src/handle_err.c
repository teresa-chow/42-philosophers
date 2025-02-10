/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 09:03:02 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/06 15:38:59 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	err_limit(void)
{
	write(2, "Invalid argument(s): value(s) below or above limit\n", 51);
	return (0);
}

int	err_philo_zero(void)
{
	write(2, "Insufficient number of philosophers to run "
		"a simulation\n", 56);
	print_usage();
	return (0);
}

void	print_usage(void)
{
	write(1, "Usage: ./philo <number_of_philosophers> <time_to_die> "
		"<time_to_eat> <time_to_sleep> "
		"[opt.: number_of_times_each_philosopher_must_eat]\n", 134);
}

int	err_mutexes(t_sim *sim)
{
	handle_mutex(&sim->print, DESTROY);
	handle_mutex(&sim->status, DESTROY);
	write(2, "Failed to create mutexes\n", 25);
	return (-1);
}

int	err_threads(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	while (i < sim->info.n_philo)
	{
		handle_mutex(&sim->forks[i], DESTROY);
		i++;
	}
	free(sim->forks);
	handle_mutex(&sim->print, DESTROY);
	handle_mutex(&sim->status, DESTROY);
	write(2, "Failed to create threads\n", 25);
	return (-1);
}
