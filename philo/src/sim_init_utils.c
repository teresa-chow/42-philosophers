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

static void	single_philo(t_sim *sim);

int	check_edge_cases(t_sim *sim)
{
	if (sim->info.n_times_to_eat == 0)
	{
		print_philos_full(sim);
		return (1);
	}
	else if (sim->info.n_philo == 1)
	{
		single_philo(sim);
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

void	monitor_sim(t_sim *sim)
{
	unsigned int	i;

	i = 0;
	while (sim_active(sim))
	{
		philos_full_checker(sim);
		if (!sim_active(sim))
			break ;
		starvation_checker(sim, i);
		i++;
		if (i == sim->info.n_philo)
			i = 0;
	}
	return ;
}

void	print_philos_full(t_sim *sim)
{
	handle_mutex(&sim->print, LOCK);
	printf(GRN "Simulation stopped: "
		"all philosophers have eaten the minimum amount of times.\n" NC);
	handle_mutex(&sim->print, UNLOCK);
}

static void	single_philo(t_sim *sim)
{
	struct timeval	now;
	unsigned long	timestamp;
	pthread_mutex_t	fork;

	handle_mutex(&fork, INIT);
	gettimeofday(&now, NULL);
	sim->start = (now.tv_sec * 1000 + now.tv_usec / 1000);
	timestamp = get_time_ms(sim);
	printf(WHI "%ld\t\t%d\t" NC CYA "is thinking\n" NC, timestamp, 1);
	handle_mutex(&fork, LOCK);
	printf(WHI "%ld\t\t%d\t" NC
				YEL "has taken a fork\n" NC, timestamp, 1);
	usleep(sim->info.time_to_die * 1000);
	timestamp = get_time_ms(sim);
	printf(WHI "%ld\t\t%d\t" NC RED "has died\n" NC, timestamp, 1);
	handle_mutex(&fork, UNLOCK);
	handle_mutex(&fork, DESTROY);
	return ;
}
