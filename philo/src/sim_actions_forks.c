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

void	acquire_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
		;
	else
	;
}

/*void	acquire_forks(t_philo *philo) //LINES TOO LONG / TOO MANY LINES
{
	unsigned int	i;
	struct timeval	now;

	i = philo->nb - 1;
	if ((i == 0 || i % 2 == 0) && (i != philo->sim->info.n_philo - 1))
	{
		pthread_mutex_lock(&philo->sim->forks[i].mutex);
		philo->sim->forks[i].taken = 1;
		gettimeofday(&now, NULL);
		printf(WHI "%ld\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec / 1000, philo->nb);
		pthread_mutex_lock(&philo->sim->forks[i + 1].mutex);
		philo->sim->forks[i + 1].taken = 1;
		gettimeofday(&now, NULL);
		printf(WHI "%ld\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec / 1000, philo->nb);
	}
	else if ((i % 2 != 0) || ((unsigned int)i == philo->sim->info.n_philo - 1))
	{
		pthread_mutex_lock(&philo->sim->forks[i - 1].mutex);
		philo->sim->forks[i - 1].taken = 1;
		gettimeofday(&now, NULL);
		printf(WHI "%ld\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec / 1000, philo->nb);
		pthread_mutex_lock(&philo->sim->forks[i].mutex);
		philo->sim->forks[i].taken = 1;
		gettimeofday(&now, NULL);
		printf(WHI "%ld\t\t%d\t" NC YEL "has taken a fork\n" NC, now.tv_usec / 1000, philo->nb);
	}
}*/

void	release_forks(t_philo *philo)
{
	unsigned int    i;

	i = philo->nb - 1;
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