/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_init_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:44:14 by tchow-so          #+#    #+#             */
/*   Updated: 2025/02/05 18:44:14 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

static void	single_philo(t_info info);

int	check_edge_cases(t_info info)
{
	if (info.n_times_to_eat == 0)
	{
		print_philos_full();
		return (1);
	}
	else if (info.n_philo == 1)
	{
		single_philo(info);
		return (1);
	}
	return (0);
}

void	assign_forks(t_sim *sim)
{
	unsigned int	i;
	unsigned int	n_philo;

	i = 0;
	n_philo = sim->info.n_philo;
	while (i < n_philo)
	{
		sim->philo[i].fork1 = &sim->forks[(i + 1) % n_philo];
		sim->philo[i].fork2 = &sim->forks[i];
		i++;
	}
	return ;
}

void	print_philos_full(void)
{
	printf(GRN "Simulation stopped: "
		"all philosophers have eaten the minimum amount of times.\n" NC);
}

static void	single_philo(t_info info)
{
	printf(WHI "%d\t\t%d\t" NC CYA "is thinking\n" NC, 0, 1);
	usleep(info.time_to_die * 1000);
	printf(WHI "%ld\t\t%d\t" NC RED "has died\n" NC, info.time_to_die, 1);
	return ;
}
