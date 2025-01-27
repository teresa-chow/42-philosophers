/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_actions_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 17:07:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_forks(int i, t_sim *sim)
{
	if ((i == 0 || i % 2 == 0) && ((unsigned int)i != sim->info.n_philo - 1))
	{
		if ((sim->forks[i].taken == 0) && (sim->forks[i + 1].taken == 0))
			return (1);
	}
	else if ((i % 2 != 0) || ((unsigned int)i == sim->info.n_philo - 1))
	{
		if ((sim->forks[i - 1].taken == 0) && (sim->forks[i].taken == 0))
			return (1);
	}
	return (0);
}

void	acquire_forks(t_philo *philo) //LINES TOO LONG / TOO MANY LINES
{
	unsigned int	i;
	struct timeval	now;

	i = philo->index;
	if ((i == 0 || i % 2 == 0) && (i != philo->sim->info.n_philo - 1))
	{
		pthread_mutex_lock(&philo->sim->forks[i].mutex);
		philo->sim->forks[i].taken = 1;
		gettimeofday(&now, NULL);
		printf(WHI "%ld\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec, i);
		pthread_mutex_lock(&philo->sim->forks[i + 1].mutex);
		philo->sim->forks[i + 1].taken = 1;
		gettimeofday(&now, NULL);
		printf(WHI "%ld\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec, i);
	}
	else if ((i % 2 != 0) || ((unsigned int)i == philo->sim->info.n_philo - 1))
	{
		pthread_mutex_lock(&philo->sim->forks[i - 1].mutex);
		philo->sim->forks[i - 1].taken = 1;
		gettimeofday(&now, NULL);
		printf(WHI "%ld\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec, i);
		pthread_mutex_lock(&philo->sim->forks[i].mutex);
		philo->sim->forks[i].taken = 1;
		gettimeofday(&now, NULL);
		printf(WHI "%ld\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec, i);
	}
}

void	release_forks(t_philo *philo)
{
	unsigned int    i;

	i = philo->index;
	if ((i == 0 || i % 2 == 0) && (i != philo->sim->info.n_philo - 1))
	{
		pthread_mutex_unlock(&philo->sim->forks[i].mutex);
		philo->sim->forks[i].taken = 0;
		pthread_mutex_unlock(&philo->sim->forks[i + 1].mutex);
		philo->sim->forks[i + 1].taken = 0;
	}
	else if ((i % 2 != 0) || (i == philo->sim->info.n_philo - 1))
	{
		pthread_mutex_unlock(&philo->sim->forks[i - 1].mutex);
		philo->sim->forks[i - 1].taken = 0;
		pthread_mutex_unlock(&philo->sim->forks[i].mutex);
		philo->sim->forks[i].taken = 0;
	}
}