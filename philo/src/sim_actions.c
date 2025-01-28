/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sim_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchow-so  <tchow-so@student.42porto.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:09 by tchow-so          #+#    #+#             */
/*   Updated: 2025/01/10 17:07:12 by tchow-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	act_think(unsigned int nb, t_philo **philo)
{
	unsigned int	i;
	struct timeval	now;

	i = nb - 1;
	if (philo[i]->sim->active == 0)
		return ;
	(*philo)[i].state = THINKING;
	gettimeofday(&now, NULL);
	printf(WHI "%ld\t\t%d\t" NC CYA "is thinking\n" NC, now.tv_usec / 1000, nb); // temp fix
	return ;
}

void	act_eat(t_info info, unsigned int nb, t_philo **philo) //review: eating after time_to_die + start_eat last time, must die
{
	unsigned int	i;
	struct timeval	now;

	i = nb - 1;
	if (philo[i]->sim->active == 0)
		return ;
	(*philo)[i].state = EATING;
	gettimeofday(&now, NULL);
	printf(WHI "%ld\t\t%d\t" NC GRN "is eating\n" NC, now.tv_usec / 1000, nb);
	usleep(info.time_to_eat);
	gettimeofday(&(*philo)[i].last_meal, NULL);
	return ;
}

void	act_sleep(t_info info, unsigned int nb, t_philo **philo)
{
	unsigned int	i;
	struct timeval	now;

	i = nb - 1;
	if (philo[i]->sim->active == 0)
		return ;
	(*philo)[i].state = SLEEPING;
	gettimeofday(&now, NULL);
	printf(WHI "%ld\t\t%d\t" NC BLU "is sleeping\n" NC, now.tv_usec / 1000, nb);
	usleep(info.time_to_sleep);
	return ;
}

void	act_die(t_sim **sim, t_info info, unsigned int nb, t_philo **philo)
{
	unsigned int	i;
	struct timeval	now;

	i = nb - 1;
	if (philo[i]->sim->active == 0)
		return ;
	gettimeofday(&now, NULL);
	if ((now.tv_usec
		- (*philo)[i].last_meal.tv_usec) > (suseconds_t)info.time_to_die * 1000)
	{
		(*philo)[i].state = STARVED;
		printf(WHI "%ld\t\t%d\t" NC RED "has died\n" NC, now.tv_usec / 1000, nb);
		(*sim)->active = 0;
	}
	return ;
}